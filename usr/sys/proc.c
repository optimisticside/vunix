#include "types.h"
#include "param.h"
#include "machdep.h"
#include "proc.h"
#include "pmap.h"
#include "lock.h"
#include "cpu.h"

/*
 * Counters for process and thread ID numbers.
 */
int mpid;
int mtid;

/*
 * Sets the given thread to be placed on the run-queue.
 */
void setrun(struct thread *td) {
	acquire(&td->lock);
	td->state = TD_READY;
	release(&td->lock);
}

/*
 * Puts the current thread to sleep. The waiting channel is any arbitrary
 * 64-bit integer or pointer, that will be stored in the thread structure. If
 * the thread is to be awaken, the same waiting channel must be provided.
 *
 * Inserts the thread into the end of the sleep queue.
 */
void sleep(void *wchan) {
	struct thread *td, *curtd;
	struct cpu *c;
	int pos;

	pos = 0;
	c = mycpu();
	curtd = c->thread;
	acquire(&curtd->lock);
	for (td = &threads[0]; td < &threads[NTHREAD]; td++) {
		if (td == curtd)
			continue;
		acquire(&td->lock);
		if (td->state == TD_SLEEP && td->wchan == wchan)
			pos++;
		release(&td->lock);
	}
	curtd->state = TD_SLEEP;
	curtd->wchan = wchan;
	curtd->wqpos = pos;

	/*
	 * swtch() will return once our context is restored, which usually
	 * when someone issues a wakeup on the channel we are sleeping on.
	 */
	release(&curtd->lock);
	swtch(&c->sched, curtd->ctx);
}

/*
 * Allocates a process structure from the process table, and assigns it
 * with a PID.
 */
struct proc *palloc(void) {
	struct proc *p, *rp;

	p = NULL;
retry:
	mpid++;
	for (rp = &procs[0]; rp < &procs[NPROC]; rp++) {
		acquire(&rp->lock);
		if (rp->pid == mpid) {
			release(&rp->lock);
			goto retry;
		}
		if (rp->state == P_NONE && p == NULL)
			p = rp;
		else
			release(&rp->lock);
	}
	p->pid = mpid;
	p->state = P_EMBRYO;
	release(&p->lock);
	return p;
}

/*
 * Wakes up all threads sleeping in the given waiting channel.
 */
void wakeup(void *wchan) {
	struct thread *td;
	
	for (td = &threads[0]; td < &threads[NTHREAD]; td++) {
		if (td->state == TD_SLEEP && td->wchan == wchan)
			setrun(td);
	}
}

/*
 * Wake up the first n threads sleeping in the given waiting channel. These
 * threads are determiend by the time at which they entered the queue (FIFO).
 */
void wakeupn(void *wchan, int n) {
	struct thread *td, *choice;

	choice = NULL;
	for (; n > 0; n--) {
		for (td = &threads[0]; td < &threads[NTHREAD]; td++) {
			acquire(&td->lock);
			if (td->state == TD_SLEEP && td->wchan == wchan
				&& (choice == NULL || td->wqpos < choice->wqpos))
				choice = td;
			release(&td->lock);
		}
		if (td == NULL)
			return;
		setrun(td);

		/*
		 * Reduce the queue position of each thread by 1. This is very
		 * inneficient, yet simplicity must come at a cost. Someday,
		 * this will be replaced by an entry in a linked-list.
		 */
		for (td = &threads[0]; td < &threads[NTHREAD]; td++) {
			acquire(&td->lock);
			if (td->wchan == wchan)
				td->wqpos--;
			release(&td->lock);
		}
	}
}

/*
 * Expand the size of the current process.
 */
int expand(int n) {
	return -1;
}

/*
 * Calculates the priority for a thread to run, using its CPU usage along with
 * other priority-related data.
 */
static int getpri(struct thread *td) {
	return td->cpu * (ticks() - td->start);
}

/*
 * Determines the next thread to be run. This is where the scheduling algorithm
 * resides.
 */
static struct thread *nexttd(void) {
	struct thread *td, *res;
	struct cpu *c;
	int usage;

	/* Update the CPU usage of the last-ran thread */
	c = mycpu();
	if ((td = c->thread) != NULL) {
		usage = ticks() - td->start;
		td->cpu = usage + (usage - td->cpu) / 3;
	}
	res = NULL;
	for (td = &threads[0]; td < &threads[NTHREAD]; td++) {
		acquire(&td->lock);
		if (td->state == TD_READY 
			&& (res == NULL || getpri(td) < getpri(res)))
			res = td;
		release(&td->lock);
	}
	if (res != NULL)
		res->start = ticks();
	return res;
}

/*
 * Infinite scheduler loop. This is called by all CPUs after setting things up.
 * It will continue to run tasks forever, and will never return.
 *
 * After that, the scheduler can only be accessed by switiching to its context,
 * which is stored in the CPU structure. Uuse sched() for this.
 */
void scheduler(void) {
	struct thread *td;
	struct cpu *c;

	c = mycpu();
	for (;;) {
		/*
		 * Find a thread to run. If no thread is found, loop
		 * indefinitely.
		 */
		while ((td = nexttd()) == NULL)
			pause();
		acquire(&td->lock);
		c->thread = td;
		pmswitch(td->proc->map);
		td->state = TD_RUN;

		/*
		 * swtch() will return when the scheduler's context is restored
		 * by some other kernel code.
		 */
		swtch(&c->sched, td->ctx);
		pmswitch(kernmap);
		td->state = TD_READY;
		release(&td->lock);
	}
}

#include "types.h"
#include "param.h"
#include "sched.h"
#include "lock.h"
#include "proc.h"
#include "cpu.h"
#include "vm.h"

/*
 * Puts the current thread to sleep. The waiting channel is any arbitrary
 * 64-bit integer or pointer, that will be stored in the thread structure. If
 * the thread is to be awaken, the same waiting channel must be provided.
 *
 * Inserts the thread into the end of the sleep queue.
 */
void sleep(void *wchan) {
	struct thread *td, *curtd;
	int pos;

	pos = 0;
	curtd = mycpu()->thread;
	acquire(&curtd->lock);
	for (td = &threads[0]; td < &threads[NTHREADS]; td++) {
		if (td == curtd)
			continue;
		acquire(&td->lock);
		if (td->state == TD_SLEEP && td->wchan == wchan)
			pos++;
		release(&td->lock);
	}
	curtd->state = TD_SLEEP;
	curtd->wchan = wchan;

	/*
	 * swtch() will return once our context is restored, which usually
	 * when someone issues a wakeup on the channel we are sleeping on.
	 */
	swtch(&cpu->sched, &curtd->ctx);
	release(&curtd->lock);
}

/*
 * Wakes up all threads sleeping in the given waiting channel.
 */
void wakeup(void *wchan) {
	struct thread *td;
	for (td = &threads[0]; td < &threads[NTHREADS]; td++) {
		if (td->state == TD_SLEEP && td->wchan == wchan)
			setrun(td);
	}
}

/*
 * Calculates the priority for a thread to run, using its CPU usage along with
 * other priority-related data.
 */
static int getpri(struct thread *td) {
	return td->usage * (tick() - td->start);
}

/*
 * Determines the next thread to be run. This is where the scheduling algorithm
 * resides.
 */
static struct thread *nexttd(void) {
	struct thread *td, res;
	struct cpu *c;
	int usage;

	/* Update the CPU usage of the last-ran thread */
	c = mycpu();
	if ((td = c->thread) != NULL) {
		usage = tick() - td->start;
		td->cpu = usage + (usage - td->cpu) / 3;
	}
	res = NULL;
	for (td = &threads[0]; td < &threads[NTHREAD]; td++) {
		if (td->state == TD_READY 
			&& (res == NULL || getpri(td) < getpri(res)))
			res = td;
	}
	if (res != NULL)
		res->start = tick();
	return res;
}

/*
 * Infinite scheduler loop. This is called by all CPUs after setting things up.
 * It will continue to run tasks forever, and will never return.
 *
 * After that, the scheduler can only be accessed by switiching to its context,
 * which is stored in the CPU structure. Uuse sched() for this.
 */
void scheduer(void) {
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
		c->thread = td;
		vmswitch(td->proc->map);
		td->state = TD_RUNNING;

		/*
		 * swtch() will return when the scheduler's context is restored
		 * by some other kernel code.
		 */
		swtch(&c->ctx, &p->ctx);
		vmswitch(kernmap);
		td->state = TD_READY;
		release(&td->lock);
	}
}

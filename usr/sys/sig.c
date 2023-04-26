#include "types.h"
#include "param.h"
#include "lock.h"
#include "proc.h"
#include "tty.h"
#include "sig.h"

/*
 * Sends a signal to an individual thread. This will still be handled by the
 * process's global signal-actions.
 */
void tdsignal(struct thread *td, int sig) {
	if (sig >= NSIG)
		return;
	acquire(&td->lock);
	td->sig |= 1 << (sig - 1);
	release(&td->lock);
}

/*
 * Sends a signal to all threads of a given process.
 */
void psignal(struct proc *p, int signo) {
	struct thread *td;

	acquire(&p->lock);
	for (td = &threads[0]; td < &threads[NTHREAD]; td++) {
		acquire(&td->lock);
		if (td->proc == p)
			tdsignal(td, signo);
		release(&td->lock);
	}
	release(&p->lock);
}

/*
 * Sends a signal to all processes who are controlled by the given teletype.
 */
void signal(struct tty *tp, int signo) {
	struct proc *p;

	acquire(&tp->lock);
	for (p = &procs[0]; p < &procs[NPROC]; p++) {
		acquire(&p->lock);
		if (p->tty == tp)
			psignal(p, signo);
		release(&p->lock);
	}
	release(&tp->lock);
}


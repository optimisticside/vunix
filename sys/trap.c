#include "types.h"
#include "param.h"
#include "proc.h"
#include "trap.h"
#include "lock.h"
#include "cpu.h"
#include "sig.h"

/*
 * User-mode trap handler. Called for all exceptions originating from processes
 * in user-mode.
 */
int utrap(struct trapframe *tf) {
	struct thread *td;
	struct proc *p;
	struct cpu *c;
	int signo, icode;
	int excp;

	c = mycpu();
	td = c->thread;

	excp = tf->scause & SCAUSE_CODE;
	switch (excp) {
	case SCAUSE_LOAD_ACCESS_FAULT:
	case SCAUSE_STORE_ACCESS_FAULT:
	case SCAUSE_INST_ACCESS_FAULT:
		signo = SIGBUS;
		icode = BUS_ADRERR;
		break;
	case SCAUSE_LOAD_MISALIGNED:
	case SCAUSE_STORE_MISALIGNED:
	case SCAUSE_INST_MISALIGNED:
		signo = SIGBUS;
		icode = BUS_ADRALN;
	default:
		printf("%d:%d - Unknown userland exception %x at %x",
			p->pid, td->tid, excp, tf->tp);	break;
	}
}

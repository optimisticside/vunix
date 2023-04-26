#ifndef _SIG_H_
#define _SIG_H_

#include "types.h"

/*
 * A signal action is something that can be called to handle a signal event,
 * and it can handle multiple types of these.
 */
struct sigact {
	void *handler;		/* Address of signal handler */
	int flags;		/* Additional flags */
	size_t mask;		/* Signal mask to apply */
};

/*
 * Macro for converting a signal number to a mask.
 */
#define SIGMASK(n)	(1 << ((n) - 1))

/*
 * Signal codes.
 */
#define SIGHUP		1	/* Hangup */
#define SIGINT		2	/* Interrupt */
#define SIGQUIT		3	/* Quit */
#define SIGILL		4	/* Illegal instruction */
#define SIGTRAP		5	/* Trace trap */
#define SIGABRT		6	/* Abort */
#define SIGKILL		9	/* Kill (cannot be caught/ignored) */
#define SIGBUS		10	/* Bus error */
#define SIGSEGV		11	/* Segmentation violation */
#define SIGSYS		12	/* Non-existent syscall invoked */
#define SIGPIPE		13	/* Wrote to pipe with no reader */
#define SIGALRM		14	/* Alaerm clock */
#define SIGTERM		15	/* Termination signal from kill */
#define SIGMAX		SIGTERM	/* Highest value of signals */

/* Codes for SIGILL */
#define ILL_ILLOPC	1	/* Illegal opcode */
#define ILL_ILLOPN	2	/* Illegal operand */
#define ILL_ILLADR	3	/* Illegal addressing mode */
#define ILL_ILLTRP	4	/* Illegal trap */
#define ILL_PRVOPC	5	/* Priviledged opcode */
#define ILL_PRVREG	6	/* Priviledged register */
#define ILL_COPROC	7	/* Coprocessor error */
#define ILL_BADSTK	8	/* Bad stack */

/* Codes for SIGBUS */
#define BUS_ADRALN	1	/* Invalid address alignment */
#define BUS_ADRERR	2	/* Nonexistent physical address */
#define BUS_OBJERR	3	/* Object-specific hardware error */

/* Codes for SIGSEGV */
#define SEGV_MAPERR	1	/* Address not mapped to object */
#define SEGV_ACCERR	2	/* Inavlid perms for mapped object */

/* Codes for SIGFPE */
#define FPE_INTOVF	1	/* Integer overflow */
#define FPE_INTDIF	2	/* Integer divide by zero */
#define FPE_FLTDIV	3	/* Floating point divide by zero */
#define FPE_FLTOVF	4	/* Floating point overflow */
#define FPE_FLTUND	5	/* Floating point underflow */
#define FPE_FLTRES	6	/* Floating point in-exact result */
#define FPE_FLTINV	7	/* Invalid floating point operation */
#define FPE_FLTSUB	8	/* Dubscript out of range */
#define FPE_FLTIDO	9	/* Input denormal operation */

/* Codes for SIGTRAP */
#define TRAP_BRKPT	1	/* Process breakpoint */
#define TRAP_TRACE	2	/* Process trace trap */
#define TRAP_DTRACE	3	/* DTrace induced trap */
#define TRAP_CAP	4	/* Capabilities protective trap */

/* Codes for SIGPOLL */
#define POLL_IN		1	/* Data input available */
#define POLL_OUT	2	/* Output buffer(s) available */
#define POLL_MSG	3	/* Input message available */
#define POLL_ERR	4	/* I/O error */
#define POLL_PRI	5	/* High priority input available */
#define POLL_HUP	6	/* Hangup (device disconnected) */

void tdsignal(struct thread *td, int signo);
void psignal(struct proc *p, int signo);
void signal(struct tty *tp, int signo);

#endif /* !_SIG_H_ */

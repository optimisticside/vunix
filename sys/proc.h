#ifndef _PROC_H_
#define _PROC_H_

#include "types.h"
#include "param.h"
#include "pmap.h"
#include "lock.h"
#include "sig.h"

/*
 * A process is defined as an independent image of execution in the operating
 * system. It is contained in its own address space.
 */
extern struct proc {
	char state;			/* Current state */
	int flags;			/* Additional flags */
	int pid;			/* Unique identifier */
	int gid;			/* User-group ID */
	int uid;			/* User ID */
	int exit;			/* Exit code */
	char name[NNAME];		/* Name (for debugging purposes) */
	struct sigact sacts[NSIG];	/* Signal actions */
	struct proc *parent;		/* Parent process (if applicable) */
	struct tty *tty;		/* Controlling teletype */
	struct pmap *map;		/* Address space */
	struct inode *cwd;		/* Current working directory */
	struct file *ofile[NOFILE];	/* Open file handles */
	struct spinlock lock;		/* Lock for modifying process */
} procs[NPROC];

/*
 * A process is composed of threads, each of which have their own stacks (both
 * for user and kernel space).
 */
extern struct thread {
	char state;			/* Current state */
	int flags;			/* Additional flags */
	int tid;			/* Unique identifier */
	int sig;			/* Signal sent */
	void *wchan;			/* Waiting channel */
	int wqpos;			/* Position in wait/sleep queue (if applicable) */
	int nice;			/* User defined bias in scheduling priority */
	int cpu;			/* Calculated CPU usage */
	int last;			/* Last time the thread ran */
	int start;			/* Time the thread started running in this cycle */
	int error;			/* Returned from syscall */
	void *kstack;			/* Start of kernel stack */
	struct proc *proc;		/* Controlling process */
	struct trapframe *tframe;	/* CPU state upon interrupt (for trampoline) */
	struct context *ctx;		/* Where to switch() to to run thread */
	struct spinlock lock;		/* Lock for modifying thread */
} threads[NTHREAD];

enum { TD_NONE, TD_READY, TD_SLEEP, TD_RUN };
enum { P_NONE, P_EMBRYO, P_ALIVE, P_DEAD, P_ZOMBIE };

struct proc *palloc(void);
struct thread *tdalloc(void);
void sched(void);
void scheduler(void);
void sleep(void *wchan);
void wakeup(void *wchan);
void wakeupn(void *wchan, int n);

#endif /* !_PROC_H_ */

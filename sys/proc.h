#ifndef _PROC_H_
#define _PROC_H_

#include "types.h"

/*
 * A process is defined as an independent image of execution in the operating
 * system. It is contained in its own address space.
 */
extern struct proc {
	char state;			/* Current state */
	uint8_t flags;			/* Additional flags */
	int pid;			/* Unique identifier */
	int exit;			/* Exit code */
	char name[NNAME];		/* Name (for debugging purposes) */
	struct proc *parent;		/* Parent process (if applicable) */
	struct tty *tty;		/* Controlling teletype */
	struct space *map;		/* Address space */
	struct inode *cwd;		/* Current working directory */
	struct file *ofile[NOFILE];	/* Open file handles */
} procs[NPROC];

/*
 * A process is composed of threads, each of which have their own stacks (both
 * for user and kernel space).
 */
extern struct thread {
	char state;			/* Current state */
	uint16_t flags;			/* Additional flags */
	int tid;			/* Unique identifier */
	int sig;			/* Signal sent */
	void *wchan;			/* Address the thread is waiting for */
	void *kstack;			/* Start of kernel stack */
	struct proc *proc;		/* Controlling process */
	struct trapframe *tframe;	/* CPU state upon interrupt (for trampoline) */
	struct context *ctx;		/* Where to switch() to to run thread */
} threads[NTHREAD];

enum { TD_NONE, TD_READY, TD_SLEEP, TD_RUN };
enum { P_NONE, P_EMBRYO, P_ALIVE, P_DEAD, P_ZOMBIE };

#endif /* !_PROC_H_ */

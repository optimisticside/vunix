#ifndef _CPU_H_
#define _CPU_H_

#include "types.h"
#include "param.h"
#include "machdep.h"

/*
 * Representation of a CPU context (function) in the kernel that can be
 * switched to. Stores the return address, stack pointer, and all registers
 * that need to be saved by the callee.
 */
struct context {
	uint64_t ra;	/* Return address */
	uint64_t sp;	/* Stack pointer */
	uint64_t s0, s1, s2, s3, s4, s5,
		 s6, s7, s8, s9, s10, s11;	/* Callee saved registers */
};

/*
 * Representation of the CPU state. Used to store and restore CPU states for
 * for interrupts and other context switches that are intra-context (kernel
 * to user mode and vice versa).
 *
 * A table of register prefixes:
 *  - a: function arguments
 *  - s: saved (by the callee)
 *  - t: temporary
 */
struct trapframe {
	uint64_t ra;				/* Return address */
	uint64_t sp;				/* Stack pointer */
	uint64_t gp;				/* Global pointer */
	uint64_t tp;				/* Thread pointer */
	uint64_t t0, t1, t2;			/* Temporary registers */
	uint64_t s0, s1, s2, s3, s4, s5,
		 s6, s7, s8, s9, s10, s11;	/* Callee saved registers */
	uint64_t a0, a1, a2, a3, a4, a5, a6, a7;/* Function arguments */
	uint64_t t3, t4, t5;			/* Temprary registers (cont) */
	uint64_t sepc, sstatus, stavl, scause;	/* Other registers */
};

/*
 * Holds all CPU-dependent information.
 */
extern struct cpu {
	struct thread *thread;	/* Currently running thread */
	struct context sched;	/* Context to switch to for scheduler loop */
	int nirq;		/* Number of nested interrupts */	
} cpus[NCPU];

/*
 * Retrieves the current CPU structure representing the current CPU.
 */
static inline struct cpu *mycpu() {
	return &cpus[cpuid()];
}

void swtch(struct context *old, struct context *new);

#endif /* !_CPU_H_ */

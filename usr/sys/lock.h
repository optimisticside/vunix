#ifndef _LOCK_H_
#define _LOCK_H_

#include "types.h"
#include "print.h"
#include "cpu.h"

/*
 * Spin-locks involve CPUs looping indefinitely until the lock's value is set
 * to false. They are used for any data that is shared across CPUs.
 */
struct spinlock {
	int value;		/* Value of the lock */
	struct cpu *cpu;	/* CPU Holding lock */
};

static inline void acquire(struct spinlock *lk) {
	if (lk->value)
		panic("spin-lock acquire");

	/* On RISC-V, sync_lock_test_and_set turns into an atomic swap: */
 	while(__sync_lock_test_and_set(&lk->value, 1) != 0)
		continue;

	/*
	 * Tell the C compiler and the CPU to not move loads or stores past
	 * this point, to ensure all stores in the critical section are visible
	 * to other CPUs before the lock is released, and that loads in the
	 * critical section occur strictly before the lock is released.
	 *
	 * On RISC-V, this emits a fence instruction.
	 */
	__sync_synchronize();
	lk->cpu = mycpu();
}

static inline void release(struct spinlock *lk) {
	lk->cpu = NULL;
	__sync_synchronize();

	/*
	 * Release the lock, equivalent to lk->locked = 0.
	 *
	 * Doesn't use a C assignment, since the C standard implies that an
	 * assignment might be implemented with multiple store instructions.
	 */
	__sync_lock_release(&lk->value);
}

#endif /* !_LOCK_H_ */

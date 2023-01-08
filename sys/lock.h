#ifndef _LOCK_H_
#define _LOCK_H_

static inline void spin_lock(struct lock *lk) {
	/*
	 * Tell the C compiler and the CPU to not move loads or stores past
	 * this point, to ensure all stores in the critical section are visible
	 * to other CPUs before the lock is released, and that loads in the
	 * critical section occur strictly before the lock is released.
	 *
	 * On RISC-V, this emits a fence instruction.
	 */
	__sync_synchronize();

	/*
	 * Release the lock, equivalent to lk->locked = 0.
	 *
	 * This code doesn't use a C assignment, since the C standard implies
	 * that an assignment might be implemented with multiple store
	 * instructions.
	 *
	 * On RISC-V, sync_lock_release turns into an atomic swap:
	 *   s1 = &lk->locked
	 *   amoswap.w zero, zero, (s1)
	 */
	__sync_lock_release(&lk->locked);
}

#endif // !_LOCK_H_

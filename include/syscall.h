#ifndef _SYSCALL_H_
#define _SYSCALL_H_

/*
 * This system-call routine can be called with any number of arguments, as it
 * is not specified (as indicated with the absence of 'void' in the
 * parameters).
 */
__attribute__ ((lp64_abi)) static inline uint64_t syscall() {
	uint64_t result;

	/*
	 * Even though the return value is already going to be stored in the a1
	 * and a2 registers, we still need to let GCC know explicitly that we
	 * are returning them in a 64-bit integer.
	 *
	 * If GCC is smart, then it will remove the move insruction altogether.
	 */
	asm volatile ("ecall; mv %0, a0" : "=r" (result));
	return result;
}

#endif /* !_SYSCALL_H_ */

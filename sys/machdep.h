#ifndef _MACHDEP_H_
#define _MACHDEP_H_

#include "types.h"

#define	SCAUSE_INTR			(1ul << 63)
#define	SCAUSE_CODE			(~SCAUSE_INTR)
#define	SCAUSE_INST_MISALIGNED		0
#define	SCAUSE_INST_ACCESS_FAULT	1
#define	SCAUSE_ILLEGAL_INSTRUCTION	2
#define	SCAUSE_BREAKPOINT		3
#define	SCAUSE_LOAD_MISALIGNED		4
#define	SCAUSE_LOAD_ACCESS_FAULT	5
#define	SCAUSE_STORE_MISALIGNED		6
#define	SCAUSE_STORE_ACCESS_FAULT	7
#define	SCAUSE_ECALL_USER		8
#define	SCAUSE_ECALL_SUPERVISOR		9
#define	SCAUSE_INST_PAGE_FAULT		12
#define	SCAUSE_LOAD_PAGE_FAULT		13
#define	SCAUSE_STORE_PAGE_FAULT		15

/*
 * Memory-mapped I/O routines.
 */
#define mmiordb(addr)		*((volatile uint8_t *)(addr))
#define mmiordw(addr)		*((volatile uint16_t *)(addr))
#define mmiordl(addr)		*((volatile uint32_t *)(addr))
#define mmiordq(addr)		*((volatile uint64_t *)(addr))
#define mmiowrb(addr, val)	(*((volatile uint8_t *)(addr)) = val)
#define mmiowrd(addr, val)	(*((volatile uint16_t *)(addr)) = val)
#define mmiowrl(addr, val)	(*((volatile uint32_t *)(addr)) = val)
#define mmiowrq(addr, val)	(*((volatile uint64_t *)(addr)) = val)

/*
 * Control and status register operations. Originally these were macros that
 * generated functions.
 */
#define wrcsr(csr, val) asm volatile ("csrw " #csr ", %0", :: "r" (val))
#define rdcsr(csr) ({					\
	uint64_t val;					\
	asm volatile ("csrr %0, " #csr : "=r" (val));	\
	val;						\
})

/*
 * Tells the CPU to wait for the next interrupt. This is used as a way to save
 * power.
 */
static inline void pause(void) {
	asm volatile ("wfi");
}

/*
 * Helper routine to get a unique identifier for a CPU.
 */
static inline int cpuid(void) {
	return rdcsr(mhartid);
}

/*
 * Gets the number of ticks of the system's real-time clock.
 */
static inline size_t ticks(void) {
	return rdcsr(time);
}

#endif /* !_MECHDEP_H_ */

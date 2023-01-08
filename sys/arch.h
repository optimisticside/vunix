#ifndef _ARCH_H_
#define _ARCH_H_

#define ARCH_SREG_READ(instr)				\
static inline uint64_t rd_##instr() {			\
	uint64_t x;					\
	asm volatile ("csrr %0, " instr : "=r" (x));	\
	return x;					\
}

#define ARCH_SREG_WRITE(instr)				\
static inline void wr_##instr(uint64_t x) {		\
	asm volatile ("csrw " instr ", %0" : "r" (x));	\
}

#define ARCH_REG_READ(reg)				\
static inline uint64_t rd_##instr() {			\
	uint64_t x;					\
	asm volatile ("mv %0, " instr : "=r" (x));	\
	return x;					\
}

#define ARCH_REG_WRITE(reg)				\
static inline void wr_##instr(uint64_t x) {		\
	asm volatile ("mv " instr ", %0" : : "r"(x));	\
}

#define ARCH_SREG_RW(instr) ARCH_SREG_READ(instr) ARCH_SREG_WRITE(instr)
#define ARCH_REG_RW(reg) ARCH_REG_READ(reg) ARCH_REG_WRITE(reg)

ARCH_SREG_READ(mhartid);
ARCH_SREG_RW(mstatus);
ARCH_SREG_RW(sstatus);
ARCH_SREG_RW(sip);
ARCH_SREG_RW(sie);
ARCH_SREG_RW(mie);
ARCH_SREG_RW(sepc);
ARCH_SREG_RW(mideleg);
ARCH_SREG_RW(medeleg);
ARCH_SREG_RW(stvec);
ARCH_SREG_RW(mtvec);
ARCH_SREG_WRITE(pmpcfg0);
ARCH_SREG_WRITE(pmpaddr0);
ARCH_SREG_RW(satp);
ARCH_SREG_RW(mscratch);
ARCH_SREG_READ(scause);
ARCH_SREG_READ(stval);
ARCH_SREG_RW(mcounteren);
ARCH_SREG_READ(time);

ARCH_REG_RW(sp);
ARCH_REG_RW(tp);
ARCH_REG_READ(ra);

#define MSTATUS_MPP_MASK (3L << 11) /* Previous mode */
#define MSTATUS_MPP_M (3L << 11)
#define MSTATUS_MPP_S (1L << 11)
#define MSTATUS_MPP_U (0L << 11)
#define MSTATUS_MIE (1L << 3)    /* Machine-mode interrupt enable */

/* Supervisor Interrupt Enable */
#define SIE_SEIE (1L << 9) /* External */
#define SIE_STIE (1L << 5) /* Timer */
#define SIE_SSIE (1L << 1) /* Software */

/* Machine-mode Interrupt Enable */
#define MIE_MEIE (1L << 11) /* External */
#define MIE_MTIE (1L << 7)  /* Timer */
#define MIE_MSIE (1L << 3)  /* Software */

#define SATP_SV39 (8L << 60)
#define MAKE_SATP(pagetable) (SATP_SV39 | (((uint64)pagetable) >> 12))

#endif /* !_ARCH_H_ */

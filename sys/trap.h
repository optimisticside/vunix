#ifndef _TRAP_H_
#define _TRAP_H_

/*
 * Exception code defenitions.
 */
#define T_INSTRADM	0	/* Instruction address misaligned */
#define T_IACCFLT	1	/* Instruction access fault */
#define T_ILLINST	2	/* Illegal instruction */
#define T_BRKPT		3	/* Breakpoint */
#define T_LDADDRM	4	/* Load address misaligned */
#define T_LDACCFLT	5	/* Load access fault */
#define T_SAMOADDRM	6	/* Store/AMO address misaligned */
#define T_SAMOAFLT	7	/* Store/AMO access fault */
#define T_UECALL	8	/* Environment call from user-mode */
#define T_SECALL	9	/* Environment call from supervisor-mode */
#define T_RESERVED	10	/* Reserved */
#define T_MECALL	11	/* Environment call from machine-mode */
#define T_IPGFLT	12	/* Instruction page fault */
#define T_RESERVED2	13	/* Reserved */
#define T_SAMOPGFLT	14	/* Store/AMO page fault */

#endif /* !_TRAP_H_ */

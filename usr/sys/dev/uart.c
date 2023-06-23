#include "types.h"
#include "param.h"
#include "machdep.h"
#include "proc.h"
#include "conf.h"

/*
 * Reference
 * [1]: TECHNICAL DATA ON 16550, http://byterunner.com/16550.html
 */

/*
 * UART control registers map. see [1] "PROGRAMMING TABLE"
 * Note some are reused by multiple functions
 * 0 (write mode): THR/DLL
 * 1 (write mode): IER/DLM
 */
#define UA_RHR	0	/* Receive Holding Register (read mode) */
#define UA_THR	0	/* Transmit Holding Register (write mode) */
#define UA_DLL	0	/* LSB of Divisor Latch (write mode) */
#define UA_IER	1	/* Interrupt Enable Register (write mode) */
#define UA_DLM	1	/* MSB of Divisor Latch (write mode) */
#define UA_FCR	2	/* FIFO Control Register (write mode) */
#define UA_ISR	2	/* Interrupt Status Register (read mode) */
#define UA_LCR	3	/* Line Control Register */
#define UA_MCR	4	/* Modem Control Register */
#define UA_LSR	5	/* Line Status Register */
#define UA_MSR	6	/* Modem Status Register */
#define UA_SPR	7	/* ScratchPad Register */

/*
 * Line stuats register flags.
 */
#define LSR_RX_FULL	1		/* Input full */
#define LSR_TX_EMPTY	(1 << 5)	/* Output empty */

void uaopen(int dev) {
	uint32_t lcr;
	uint8_t ier;

	/*
	 * Setting baud rate. Just a demo here if we care about the divisor,
	 * but for our purpose [QEMU-virt], this doesn't really do anything.
	 *
	 * Notice that the divisor register DLL (divisor latch least) and DLM
	 * (divisor latch most) have the same base address as the
	 * receiver/transmitter and the interrupt enable register. To change
	 * what the base address points to, we open the "divisor latch" by
	 * writing 1 into the Divisor Latch Access Bit (DLAB), which is bit
	 * index 7 of the Line Control Register (LCR).
	 *
	 * Regarding the baud rate value, see:
	 * [1] "BAUD RATE GENERATOR PROGRAMMING TABLE".
	 * We use 38.4K when 1.8432 MHZ crystal, so the corresponding value is
	 * 3. And due to the divisor register is two bytes (16 bits), so we
	 * need to split the value of 3(0x0003) into two bytes, DLL stores the
	 * low byte, DLM stores the high byte.
	 */
	mmiowrb(UART0 + UA_IER, 0x00);
	lcr = mmiordb(UART0 + UA_LCR);
	mmiowrb(UART0 + UA_LCR, lcr | (1 << 7));
	mmiowrb(UART0 + UA_DLL, 0x03);
	mmiowrb(UART0 + UA_DLM, 0x00);

	/*
	 * Continue setting the asynchronous data communication format, and
	 * enable interrupts.
	 */
	lcr = 0;
	mmiowrb(UART0 + UA_LCR, lcr | (3 << 0));
	ier = mmiordb(UART0 + UA_IER);
	mmiowrb(UART0 + UA_IER, ier | (1 << 0));
}

void uaputc(int dev, int c) {
	while ((mmiordb(UART0 + UA_LSR) & LSR_TX_EMPTY) == 0)
		continue;
	mmiordb(UART0 + UA_THR, ch);
}

int uagetc(int dev) {
	if (mmiordb(UART0 + UA_LSR) & LSR_RX_READY)
		return mmiordb(UART0 + UA_RHR);
	return -1;
}

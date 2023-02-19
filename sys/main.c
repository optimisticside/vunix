#include "types.h"
#include "param.h"
#include "string.h"
#include "filsys.h"
#include "inode.h"
#include "mount.h"
#include "conf.h"
#include "lock.h"
#include "proc.h"
#include "cpu.h"
#include "buf.h"
#include "tty.h"

__attribute__ ((aligned (16))) char stack0[4096 * NCPU];

/*
 * Set by the first CPU after it has completed the initialization process. All
 * other CPUs will wait for this to be set before starting.
 */
int started = 0;

/*
 * I-Node initialization routine. Reads the root-device's superblock and
 * initializes the current date from the last modified date.
 */
struct superblock *iinit(void) {
	struct buf *cp, *bp;
	struct thread *td;

	td = mycpu()->thread;
	blkdevs[major(ROOTDEV)].open(ROOTDEV);
	bp = bread(ROOTDEV, SUPER_BLKNO);
	cp = geteblk();
	if (td->error)
		panic("iinit");
	memcpy(bp->addr, cp->addr, sizeof(struct superblock *));
	brelease(bp);
	mounts[0].buf = cp;
	mounts[0].dev = ROOTDEV;
	return cp->addr;
}

#define UART        0x10000000
#define UART_THR    (uint8_t*)(UART+0x00) // THR:transmitter holding register
#define UART_LSR    (uint8_t*)(UART+0x05) // LSR:line status register
#define UART_LSR_EMPTY_MASK 0x40          // LSR Bit 6: Transmitter empty; both the THR and LSR are empty

int lib_putc(char ch) {
	while ((*UART_LSR & UART_LSR_EMPTY_MASK) == 0);
	return *UART_THR = ch;
}

void lib_puts(char *s) {
	while (*s) lib_putc(*s++);
}

/*
 * Main kernel initialization routine. This can be only called on one cpu.
 */
void start(void) {
	struct superblock *sb;
	struct thread *td;
	struct proc *p;

	// for testing purposes.
	lib_puts("Hello world\n");

	p = palloc();
	td = tdalloc();
	td->proc = p;
	td->state = TD_RUN;
	mycpu()->thread = td;

	cbinit();
	binit();
	sb = iinit();

	chrdevs[major(CONSDEV)].open(CONSDEV);
	rootdir = iget(ROOTDEV, rootino(sb));
	rootdir->flags &= I_LOCK;
	started = 1;
}

/*
 * Main entry point for kernel. Called by bootloader and other assembly code.
 * Hands control onto start() and ultimately the scheduler. 
 */
void main(void) {
	if (cpuid() == 0)
		start();
	while (!started)
		continue;
	scheduler();
}

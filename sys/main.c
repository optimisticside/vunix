#include "types.h"
#include "param.h"
#include "inode.h"
#include "conf.h"
#include "lock.h"
#include "proc.h"
#include "cpu.h"
#include "buf.h"
#include "tty.h"

/*
 * Set by the first CPU after it has completed the initialization process. All
 * other CPUs will wait for this to be set before starting.
 */
int started = 0;

/*
 * Main kernel initialization routine. This can be only called on one cpu.
 */
void start(void) {
	struct thread *td;
	struct proc *p;

	p = palloc();
	td = tdalloc();
	td->proc = p;
	td->state = TD_RUN;
	mycpu()->thread = td;

	cinit();
	binit();
	iinit();

	chrdevs[major(CONS_DEV)].open(CONS_DEV);
	rootdir = iget(ROOT_DEV, ROOT_INO);
	rootdir->flags &= I_LOCK;
	started = 1;
}

/*
 * I-Node initialization routine. Reads the root-device's superblock and
 * initializes the current date from the last modified date.
 */
void iinit(void) {
	struct buf *cp, *bp;
	struct thread *td;

	td = mycpu()->thread;
	blkdevs[major(ROOT_DEV)].open(ROOT_DEV);
	bp = bread(ROOT_DEV, SUPERBLKNO);
	cp = balloc();
	if (td->error)
		panic("iinit");
	memcpy(bp->addr, cp->addr, sizeof(struct superblock *));
	brelease(bp);
	mounts[0].buf = cp;
	mounts[0].dev = rootdev;
}

/*
 * Main entry point for kernel. Called by bootloader and other assembly code.
 * Hands contrl onto start() and ultimately the scheduler.
 */
void main(void) {
	if (cpuid() == 0)
		start();
	while (!started)
		continue;
	scheduler();
}

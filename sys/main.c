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
 * I-Node initialization routine. Reads the root-device's superblock and
 * initializes the current date from the last modified date.
 */
void iinit(void) {
	struct buf *cp, *bp;
	struct thread *td;

	td = mycpu()->thread;
	blkdevs[major(rootdev)].open(rootdev);
	bp = bread(rootdev, SUPERBLKNO);
	cp = balloc();
	if (td->error)
		panic("iinit");
	memcpy(bp->addr, cp->addr, sizeof(struct superblock *));
	brelease(bp);
	mount[0].buf = cp;
	mount[0].dev = rootdev;
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

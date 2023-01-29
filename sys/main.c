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
	blkdevs[major(ROOT_DEV)].open(ROOT_DEV);
	bp = bread(ROOT_DEV, SUPER_BLKNO);
	cp = geteblk();
	if (td->error)
		panic("iinit");
	memcpy(bp->addr, cp->addr, sizeof(struct superblock *));
	brelease(bp);
	mounts[0].buf = cp;
	mounts[0].dev = ROOT_DEV;
	return cp->addr;
}

/*
 * Main kernel initialization routine. This can be only called on one cpu.
 */
void start(void) {
	struct superblock *sb;
	struct thread *td;
	struct proc *p;

	p = palloc();
	td = tdalloc();
	td->proc = p;
	td->state = TD_RUN;
	mycpu()->thread = td;

	cinit();
	binit();
	sb = iinit();

	chrdevs[major(CONS_DEV)].open(CONS_DEV);
	rootdir = iget(ROOT_DEV, rootino(sb));
	rootdir->flags &= I_LOCK;
	started = 1;
}

/*
 * Main entry point for kernel. Called by bootloader and other assembly code.
 * Hands control onto start() and ultimately the scheduler. 
 */
void main(void) {
	if (rd_mhartid() == 0)
		start();
	while (!started)
		continue;
	scheduler();
}

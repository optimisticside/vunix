#include "types.h"
#include "param.h"
#include "conf.h"
#include "proc.h"
#include "buf.h"

/*
 * Pick up the device's error number and pass it to the user. If there is an
 * error but the number is 0 set a generalized code. Actually the latter is
 * always true because devices don't yet return specific errors.
 */
void geterror(struct buf *bp) {
	struct thread *td;

	td = mycpu()->thread;
	if ((td->error = bp->error) == 0)
		td->error = EIO;
}

/*
 * Yields until I/O completion on provided buffer. Returns error to the user.
 */
void iowait(struct buf *bp) {
	while ((bp->flags&B_DONE) == 0)
		sleep(bp);
	geterror(bp);
}

/*
 * Allocates buffer and reads from device into buffer (or yields for buffer to
 * be available).
 */
static struct buf *getblk(int dev, uint64_t blkno, int size) {
	struct devtab *dt;
	struct buf *bp;

	if (major(dev) < NBLDEV)
		panic("blkdev");
	for (;;) {
		if ((dt = blkdevs[major(dev)].tab) == NULL)
			panic("devtab");
		for (bp = dt->head; bp != NULL; bp = bp->forw) {
			if (bp->blkno != blkno || bp->dev != dev || bp->size != size)
				continue;
			if (bp->flags & B_LOCK) {
				sleep(bp);
				continue;
			}
			bp->flags |= B_LOCK;
		}
		if ((bp = balloc()) == NULL) {
			sleep(bfreelist);
			continue;
		}
		if (bp->flags & B_DIRTY)
			bsync(bp);
		bp->back->forw = bp->forw;
		bp->forw->back = bp->back;
		bp->dev = dev;
		bp->blkno = blkno;
		bp->size = size;
		return bp;
	}
}

/*
 * Reads reads a block from a block device, allocates a buffer to store the
 * data, and returns the allocated buffer.
 *
 * If no buffer is found, then yields for a buffer to be available.
 */
struct buf *bread(int dev, uint64_t blkno, int size) {
	struct buf *bp;

	bp = getblk(dev, blkno, size);
	if (bp->flags B_VALID)
		return bp;
	bp->flags |= B_READ;
	blkdevs[major(dev)].strat(bp);
	iowait(bp);
	return bp;
}

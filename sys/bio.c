#include "types.h"
#include "param.h"
#include "conf.h"
#include "proc.h"
#include "buf.h"

/*
 * Finds a block of the given block-number and of the given device, with the
 * given size.
 */
static struct buf *findblk(int dev, uint64_t blk, int sz) {
	struct buf *bp;

	for (bp = &bufs[0]; bp < &bufs[NBUF]; bp++) {
		if (bp->dev == dev && bp->blk == blk && bp->size == sz)
			return bp;
	}
}

/*
 * Sync a buffer with disk.
 */
static void bsync(struct buf *bp) {
	struct blkdev *d;

	if ((d = getbdev(bp->dev)) == NULL)
		panic("bufdev");
	(*d->strat)(bp);
}

/*
 * Allocates buffer and reads from device into buffer (or yields for buffer to
 * be available).
 */
static struct buf *getblk(int dev, uint64_t blk, int sz) {
	struct buf *bp;

	for (;;) {
		if ((bp = findblk(dev, blk, sz)) != NULL) {
			if (bp->flags & B_LOCK) {
				sleep(bp);
				continue;
			}
			bp->flags |= B_LOCK;
			return bp;
		}
		if ((bp = balloc()) == NULL) {
			sleep(bfreelist);
			continue;
		}
		if (bp->flags & B_DIRTY)
			bsync(bp);
		bp->dev = dev;
		bp->blk = blk;
		bp->size = sz;
		return bp;
	}
}

/*
 * Reads reads a block from a block device, allocates a buffer to store the
 * data, and returns the allocated buffer.
 *
 * If no buffer is found, then yields for a buffer to be available.
 */
struct buf *bread(int dev, uint64_t blk, int sz) {
	struct buf *bp;
	
	if ((bp = getblk(dev, blk, sz)) != NULL) {
		
	}
}

#include "types.h"
#include "param.h"
#include "conf.h"
#include "proc.h"
#include "buf.h"

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
	struct devtab *dt;
	struct buf *bp;

	if (major(dev) < NBLDEV)
		panic("blkdev");
	for (;;) {
		if ((dt = blkdevs[major(dev)].tab) == NULL)
			panic("devtab");
		for (bp = dt->head; bp != NULL; bp = bp->forw) {
			if (bp->blk != blk || bp->dev != dev)
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

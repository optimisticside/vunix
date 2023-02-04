#include "types.h"
#include "param.h"
#include "print.h"
#include "conf.h"
#include "proc.h"
#include "buf.h"
#include "cpu.h"

struct {
	struct spinlock lock;	/* Spin lock */
	struct buf *head;	/* First buffer in list */
	struct buf *tail;	/* Last buffer in list */
} bfreelist;

/*
 * Retrieves an empty buffer.
 */
struct buf *geteblk(void) {
	struct buf *bp;

	for (;;) {
		acquire(&bfreelist.lock);
		if ((bp = bfreelist.head) == NULL)
			continue;
		acquire(&bp->lock);
		bfreelist.head = bp->forw;
		bp->forw = NULL;
		if (bp == bfreelist.tail)
			bfreelist.tail = NULL;
		release(&bfreelist.lock);
		if (bp->flags&B_DIRTY) {
			bp->flags |= B_ASYNC;
			bwrite(bp);
			release(&bp->lock);
			continue;
		}
		bp->flags |= B_LOCK;
		release(&bp->lock);
		return bp;
	}
}

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
static struct buf *getblk(int dev, size_t blkno, int size) {
	struct devtab *dt;
	struct buf *bp;

	if (major(dev) < NBLKDEV)
		panic("blkdev");

loop:
	if ((dt = blkdevs[major(dev)].tab) == NULL)
		panic("devtab");
	for (bp = dt->head; bp != NULL; bp = bp->forw) {
		acquire(&bp->lock);
		if (bp->blkno != blkno || bp->dev != dev || bp->size != size)
			goto loop;
		if (bp->flags & B_LOCK) {
			release(&bp->lock);
			sleep(bp);
			goto loop;
		}
		bp->flags |= B_LOCK;
		release(&bp->lock);
		return bp;
	}
	acquire(&bfreelist.lock);
	if ((bp = bfreelist.head) == NULL) {
		release(&bfreelist.lock);
		sleep(&bfreelist);
		goto loop;
	}
	acquire(&bp->lock);
	bfreelist.head = bp->forw;
	bp->forw = NULL;
	if (bp == bfreelist.tail)
		bfreelist.tail = NULL;
	release(&bfreelist.lock);
	if (bp->flags & B_DIRTY) {
		bp->flags |= B_ASYNC;
		bwrite(bp);
		release(&bp->lock);
		goto loop;
	}
	bp->flags |= B_LOCK;
	bp->dev = dev;
	bp->blkno = blkno;
	bp->size = size;
	release(&bp->lock);
	return bp;
}

/*
 * Reads reads a block from a block device, allocates a buffer to store the
 * data, and returns the allocated buffer.
 *
 * If no buffer is found, then yields for a buffer to be available.
 */
struct buf *bread(int dev, uint64_t blkno) {
	struct buf *bp;
	int size;

	size = blkdevs[major(dev)].blksz;
	bp = getblk(dev, blkno, size);
	if (bp->flags&B_DONE)
		return bp;
	bp->flags |= B_READ;
	blkdevs[major(dev)].strat(bp);
	iowait(bp);
	return bp;
}

/*
 * Writes the buffer to its device and releases the buffer.
 */
void bwrite(struct buf *bp) {
	int flags;

	flags = bp->flags;
	bp->flags &= ~(B_WRITE | B_DONE | B_ERROR | B_DELWRI);
	blkdevs[minor(bp->dev)].strat(bp);
	if (flags & B_ASYNC == 0) {
		iowait(bp);
		brelease(bp);
	} else if (flags & B_DELWRI == 0)
		geterror(bp);
}

/*
 * Initialize all buffers. The only thing that needs to be done is moving them
 * all to the freelist. No locks are needed since this runs on one CPU only,
 * but are still used for good measure.
 */
void binit(void) {
	struct buf *bp;

	acquire(&bfreelist.lock);
	for (bp = &bufs[0]; bp < &bufs[NBUF]; bp++) {
		acquire(&bp->lock);
		bp->forw = bfreelist.head;
		if (bfreelist.tail == NULL)
			bfreelist.tail = bp;
		bfreelist.head = bp;
		release(&bp->lock);
	}
	release(&bfreelist.lock);
}

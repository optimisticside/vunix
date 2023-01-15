#ifndef _BUF_H_
#define _BUF_H_

#include "types.h"

/*
 * A buffer is the center of all I/O operations on block devices like
 * disks. They also serve as a cache for data that is stored on the block
 * device.
 *
 * The structure below is not actually the buffer, but the header of the
 * buffer (the actual buffer comes right after this structure).
 */
extern struct buf {
	int flags;		/* Additional flags */
	struct buf *forw;	/* Next buffer in queue */
	struct buf *prev;	/* Previous buffer in queue */
	uint64_t blkno;		/* Block number on device */
	int dev;		/* ID of device */
	int error;		/* Error returned from I/O */
} bufs[NBUF];

/*
 * Each block device has a device-table, which contrains private stuff and
 * two doubly linked-lists that contain all buffers associated with that major
 * device.
 */
struct devtab {
	struct buf *head;	/* First buffer for this device */
	struct buf *tail;	/* Last buffer for this device */
	struct buf *iohead;	/* Head of I/O queue */
	struct buf *iotail;	/* Tail of I/O queue */
};

#define	B_WRITE	0		/* Non-read pseudo-flag */
#define	B_READ	1		/* Read when I/O occurs */
#define	B_DONE	2		/* Transaction finished */
#define	B_ERROR	4		/* Transaction aborted */
#define	B_BUSY	8		/* Not on free list */
#define	B_PHYS	16		/* Physical I/O */
#define	B_WANTED 64		/* Issue wakeup when BUSY goes off */
#define	B_RELOC	128		/* No longer used */
#define	B_ASYNC	246		/* Don't wait for I/O completion */
#define	B_DELWRI 512		/* Don't write till block leaves available list */

struct buf *bread(int dev, uint64_t blkno, int size);
void brelease(struct buf *bp);
void bwrite(struct buf *bp);

#endif /* !_BUF_H_ */

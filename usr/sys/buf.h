#ifndef _BUF_H_
#define _BUF_H_

#include "types.h"
#include "param.h"
#include "lock.h"

/*
 * A buffer is the center of all I/O operations on block devices like
 * disks. They also serve as a cache for data that is stored on the block
 * device.
 *
 * The structure below is not actually the buffer, but the header of the
 * buffer (the actual buffer comes right after this structure).
 */
extern struct buf {
	struct spinlock lock;	/* Spin lock */
	struct buf *forw;	/* Next buffer in queue */
	struct buf *back;	/* Previous buffer in queue */
	uint64_t blkno;		/* Block number on device */
	void *addr;		/* Address to start of buffer (usually end of struct) */
	int flags;		/* Additional flags */
	int size;		/* Block size */
	int dev;		/* ID of device */
	int error;		/* Error returned from I/O */
} bufs[NBUF];

/*
 * Each block device has a device-table, which contrains private stuff and
 * two doubly linked-lists that contain all buffers associated with that major
 * device.
 */
struct devtab {
	struct spinlock lock;	/* Spin lock */
	struct buf *head;	/* First buffer for this device */
	struct buf *tail;	/* Last buffer for this device */
	struct buf *iohead;	/* Head of I/O queue */
	struct buf *iotail;	/* Tail of I/O queue */
};

#define	B_WRITE		0	/* Non-read pseudo-flag */
#define	B_READ		1	/* Read when I/O occurs */
#define	B_DONE		2	/* Transaction finished */
#define	B_ERROR		4	/* Transaction aborted */
#define	B_BUSY		8	/* Not on free list */
#define	B_PHYS		16	/* Physical I/O */
#define B_DIRTY 	32	/* Not synced with disk */
#define B_LOCK		64	/* In use */
#define	B_WANTED	64	/* Issue wakeup when BUSY goes off */
#define	B_RELOC		128	/* No longer used */
#define	B_ASYNC		246	/* Don't wait for I/O completion */

void binit(void);
struct buf *bread(int dev, size_t blkno);
struct buf *breada(int dev, size_t blkno, size_t rablkno);
void brelse(struct buf *bp);
void bwrite(struct buf *bp);
struct buf *geteblk(void);

#endif /* !_BUF_H_ */

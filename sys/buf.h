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

#endif /* !_BUF_H_ */

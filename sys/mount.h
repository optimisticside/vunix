#ifndef _MOUNT_H_
#define _MOUNT_H_

#include "types.h"
#include "param.h"
#include "lock.h"

/*
 * Mounts allow the use of multiple file-systems or disks in the same
 * file-system hierarchy (virtual file-system).
 */
extern struct mount {
	struct spinlock lock;	/* Spin lock */
	struct inode *inode;	/* Mounted I-Node */
	struct buf *buf;	/* Pointer to superblock */
	int dev;		/* Device mounted */
} mounts[NMOUNT];

#endif /* !_MOUNT_H_ */

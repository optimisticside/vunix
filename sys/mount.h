#ifndef _MOUNT_H_
#define _MOUNT_H_

#include "types.h"
#include "param.h"

/*
 * Mounts allow the use of multiple file-systems or disks in the same
 * file-system hierarchy (virtual file-system).
 */
extern struct mount {
	int dev;		/* Device mounted */
	struct buf *buf;	/* Pointer to superblock */
	struct inode *inode;	/* Mounted I-Node */
} mounts[NMOUNT];

#endif /* !_MOUNT_H_ */

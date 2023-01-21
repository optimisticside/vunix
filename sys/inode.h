#ifndef _INODE_H_
#define _INODE_H_

#include "types.h"

/*
 * An I-Node is the center of all file-system operations done. It represents a
 * node in the file system, whether that be a directory, file, or some device.
 */
struct inode {
	int flags;		/* Additional flags */
	char count;		/* Reference count */
	int dev;		/* Device number */
	uint64_t num;		/* I-node number on device */
	short nlink;		/* Directory entries */
	short uid;		/* Owner */
	short gid;		/* Group of owner */
	uint64_t size;		/* Size of file */
}

#endif /* !_INODE_H_ */

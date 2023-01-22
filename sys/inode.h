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
	uint16_t mode;		/* Access mode */
	short nlink;		/* Directory entries */
	short uid;		/* Owner */
	short gid;		/* Group of owner */
	uint64_t size;		/* Size of file */
}

/* Flag defenitions */
#define I_LOCK	1		/* Locked */
#define I_UPD	2		/* Updated */
#define I_ACC	4		/* Accessed */
#define I_MOUNT	8		/* Mounted */
#define I_WANT	12		/* Wanted */
#define I_CHG	16		/* Modified */

#endif /* !_INODE_H_ */

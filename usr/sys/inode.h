#ifndef _INODE_H_
#define _INODE_H_

#include "types.h"
#include "lock.h"

/*
 * An I-Node is the center of all file-system operations done. It represents a
 * node in the file system, whether that be a directory, file, or some device.
 */
extern struct inode {
	struct spinlock lock;	/* Spin lock */
	int flags;		/* Additional flags */
	char count;		/* Reference count */
	int dev;		/* Device number */
	size_t num;		/* I-node number on device */
	int mode;		/* Access mode */
	int nlink;		/* Directory entries */
	int uid;		/* Owner */
	int gid;		/* Group of owner */
	size_t size;		/* Size of file */
} inodes[NINODE], *rootdir;

/* Flag defenitions */
#define I_LOCK	1		/* Locked */
#define I_UPD	2		/* Updated */
#define I_ACC	4		/* Accessed */
#define I_MOUNT	8		/* Mounted */
#define I_WANT	12		/* Wanted */
#define I_CHG	16		/* Modified */

struct inode *iget(int dev, size_t ino);
void iput(struct inode *ip);
void readi(struct inode *ip, void *buf, size_t offset, size_t count);
void writei(struct inode *ip, void *buf, size_t offset, size_t count);
struct inode *namei(char *path);

#endif /* !_INODE_H_ */

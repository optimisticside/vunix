#include "types.h"
#include "param.h"
#include "inode.h"
#include "conf.h"
#include "proc.h"
#include "lock.h"

/*
 * Reads from a file given its corresponding I-Node.
 */
void readi(struct inode *ip, size_t offset, void *buf, size_t count) {
	struct thread *td;
	struct buf *bp;
	int bshift, bmask, dev;
	size_t blksz, blkno;

	dev = ip->dev;
	td = mycpu()->thread;
	if ((ip->mode & I_FMT) == IF_CHAR)
		return (*chrdevs[major(dev)].read)(minor(dev));
	blksz = blkdevs[major(dev)].blksz;
	bshift = log2(blksz);
	blkno = offset >> bshift;
	do {

	} while (td->error == 0 && count == 0);
}

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
	size_t blksiz, blkno;

	dev = ip->dev;
	td = mycpu()->thread;
	if ((ip->mode & I_FMT) == IF_CHAR)
		return (*chrdevs[major(dev)].read)(minor(dev));
	blksiz = blkdevs[major(dev)].blksiz;
	bshift = log2(blksiz);
	blkno = offset >> bshift;
	do {

	} while (td->error == 0 && count == 0);
}

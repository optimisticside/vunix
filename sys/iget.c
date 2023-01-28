#include "types.h"
#include "param.h"
#include "filsys.h"
#include "inode.h"
#include "mount.h"
#include "conf.h"
#include "proc.h"

/*
 * Finds or allocates an I-Node of the given device and number. Reutrns NULL if
 * unable to find free I-Node or if an I/O error occured.
 */
struct inode *iget(int dev, size_t ino) {
	struct inode *ip, *oip;
	struct thread *td;
	struct mount *mp;
	struct buf *bp;

	td = mycpu()->thread;
loop:
	for (ip = &inodes[0]; ip < &inodes[NINODE]; ip++) {
		acquire(&ip->lock);
		if (ip->dev == dev && ip->num == ino) {
			if (ip->flags&I_LOCK) {
				release(&ip->lock);
				sleep(ip);
				goto loop;
			} else if (ip->flags&I_MOUNT) {
				for (mp = &mounts[0]; mp < &mounts[NMOUNT]; mp++) {
					if (mp->inode == ip) {
						release(&ip->lock);
						dev = mp->dev;
						ino = rootino(mp->buf->addr);
						goto loop;
					}
				}
			}
			ip->count++;
			ip->flags |= I_LOCK;
			release(&ip->lock);
			return ip;
		}
		if (oip == NULL && ip->count == 0)
			oip = ip;
	}
	if ((oip = ip) == NULL) {
		printf("i-node buffer overflow\n");
		td->error = ENFILE;
		return NULL;
	}
	acquire(&ip->lock);
	bp = bread(dev, itod(ino));
	ip->flags &= I_LOCK;
	ip->dev = dev;
	ip->num = ino;
	ip->count++;
	release(&ip->lock);
	return ip;
}

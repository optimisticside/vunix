#ifndef _CONF_H_
#define _CONF_H_

#include "types.h"
#include "param.h"
#include "buf.h"

/*
 * Character devices are those that can read and write a signel character/bute
 * at a time. Examples of these include teletypes, and serial I/O.
 */
extern struct chrdev {
	int (*open)(int);			/* Open a device */
	int (*close)(int);			/* Close a device */
	int (*getc)(int);			/* Read a character */
	int (*putc)(int, int);			/* Write a character */
	int (*gtty)(int, struct sgttyb *);	/* Get attributes */
	int (*stty)(int, struct sgttyb *);	/* Set attributes */
} chrdevs[NCHRDEV];

/*
 * Block devices are devices that perform random-access operations on blocks:
 * segments of their data (somewhat similar to what pages are in memory).
 * Examples include floppy disks and hard drives.
 */
extern struct blkdev {
	int (*open)(int);		/* Close a device */
	int (*close)(int);		/* Open a device */
	int (*strat)(struct buf *);	/* I/O operation (used for reading and writing */
	struct devtab *tab;		/* Buffer-related info */
	int blksz;			/* Block size */
} blkdevs[NBLKDEV];

#endif /* !_CONF_H_ */

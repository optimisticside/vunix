#ifndef _CONF_H_
#define _CONF_H_

#include "types.h"

/*
 * Character devices are those that can read and write a signel character/bute
 * at a time. Examples of these include teletypes, and serial I/O.
 */
struct chardev {
	int (*open)(int);	/* Open a device */
	int (*close)(int);	/* Close a device */
	int (*getc)();		/* Read a character */
	int (*putc)(int);	/* Write a character */
	int (*canrd)();		/* Determine whether a character can be read */
	int (*canwr)();		/* Determine whether a character can be written */
}

/*
 * Block devices are devices that perform random-access operations on blocks:
 * segments of their data (somewhat similar to what pages are in memory).
 * Examples include floppy disks and hard drives.
 */
struct blkdev {
	int (*open)(int);		/* Close a device */
	int (*close)(int);		/* Open a device */
	int (*strat)(struct buf *);	/* I/O operation (used for reading and writing */
}

#endif /* !_CONF_H_ */

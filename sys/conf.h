#ifndef _CONF_H_
#define _CONF_H_

#include "types.h"

/*
 * Character devices are those that can read and write a signel character/bute
 * at a time. Examples of these include teletypes, and serial I/O.
 */
struct chardev {
	int (*open)(dev_t);	/* Open a device */
	int (*close)(dev_t);	/* Close a device */
	int (*getc)();		/* Read a character */
	int (*putc)(int);	/* Write a character */
	int (*state)();		/* Get a character-device state (see below) */
}

/*
 * Block devices are devices that perform random-access operations on blocks:
 * segments of their data (somewhat similar to what pages are in memory).
 * Examples include floppy disks and hard drives.
 */t a
struct blkdev {
	int (*open)(dev_t);		/* Close a device */
	int (*close)(dev_t);		/* Open a device */
	int (*strat)(struct buf *);	/* I/O operation (used for reading and writing */
}

#endif /* !_CONF_H_ */

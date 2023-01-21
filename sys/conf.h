#ifndef _CONF_H_
#define _CONF_H_

#include "types.h"
#include "param.h"

/*
 * Character devices are those that can read and write a signel character/bute
 * at a time. Examples of these include teletypes, and serial I/O.
 */
extern struct chrdev {
	int (*open)(int);	/* Open a device */
	int (*close)(int);	/* Close a device */
	int (*getc)();		/* Read a character */
	int (*putc)(int);	/* Write a character */
	int (*canrd)();		/* Determine whether a character can be read */
	int (*canwr)();		/* Determine whether a character can be written */
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
} blkdevs[NBLKDEV];

#endif /* !_CONF_H_ */

#ifndef _TTY_H_
#define _TTY_H_

#include "types.h"
#include "param.h"
#include "lock.h"

/*
 * Structure for stty and gtty system calls.
 */
struct sgttyb {
	char ispeed;		/* Input speed */
	char ospeed;		/* Output speed */
	char erase;		/* Erase character */
	char kill;		/* Kill character */
	int flags;		/* Mode flags */
};

/* 
 * One allocated per entry in character list. Characters in each block are
 * added to in reverse order. For example, if there was only 1 character in a
 * block, the block would be all zeros except its last byte.
 */
extern struct cblock {
	struct spinlock lock;	/* Spin lock */
	struct cblock *forw;	/* Next entry in character list */
	char chars[CBLKSIZ];	/* Data */
	size_t size;		/* Size of data (to save time) */
} cblocks[NCBLOCK];

/*
 * Handles all data going through character devices that are connected to
 * terminals/teletypes. Acts as an abstraction layer over character devices
 * that takes care of buffering and escape sequences for doing things such as
 * sending signals.
 *
 * You can think of these as the character-device equivalent of buffers.
 */
extern struct tty {
	struct spinlock lock;	/* Spin lock */
	struct cblock rawq;	/* Input characters from device */
	struct cblock canq;	/* Input characters afer erase+kill */
	struct cblock outq;	/* Output queue to device */
	int col;		/* Current column */
	int flags;		/* Additional flags */
	int dev;		/* Device number */
	char erase;		/* Erase character */
	char kill;		/* Kill character */
	char ispeed;		/* Input speed (ms) */
	char ospeed;		/* Output speed (ms) */
} ttys[NTTY];

void cbinit(void);

#endif /* !_TTY_H_ */

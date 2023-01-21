#ifndef _TTY_H_
#define _TTY_H_

/* 
 * One allocated per entry in character list.
 */
struct clist {
	struct clistent *next;	/* Next entry in character list */
	char chars[32];		/* Data */
};

/*
 * Handles all data going through character devices that are connected to
 * terminals/teletypes. Acts as an abstraction layer over character devices
 * that takes care of buffering and escape sequences for doing things such as
 * sending signals.
 *
 * You can think of these as the character-device equivalent of buffers.
 */
extern struct tty {
	struct clist rawq;	/* Input characters from device */
	struct clist canq;	/* Input characters afer erase+kill */
	sturct clist outq;	/* Output queue to device */
	int flags;		/* Additional flags */
	int dev;		/* Device number */
	char erase;		/* Erase character */
	char kill;		/* Kill character */
	int ispeed;		/* Input speed (ms) */
	int ospeed/		/* Output speed (ms) */
} ttys[NTTY];

#endif /* !_TTY_H_ */

#ifndef _CALLO_H_
#define _CALLO_H_

#include "types.h"
#include "lock.h"

/*
 * A callout is a function that will be called within a certain time-interval.
 * Note that the function can only take one argument.
 */
extern struct callo {
	struct spinlock lock;	/* Spin lock */
	size_t time;		/* Incremental time */
	void *arg;		/* Argument to provide to function */
	void (*func)(void *);	/* Routine to call */
} callos[NCALLO];

#endif /* !_CALLO_H_ */

#ifndef _CALLO_H_
#define _CALLO_H_

#include "types.h"

/*
 * A callout is a function that will be called within a certain time-interval.
 * Note that the function must be able to accept parameters pushed onto the
 * the stack, as that is the only way we can actually pass paramters to it.
 */
extern struct callout {
	size_t time;		/* Incremental time */
	int nargs;		/* Argument count */
	void *args[];		/* Function arguments */
	void (*func)();		/* Routine to call */
} callouts;

#endif /* !_CALLO_H_ */

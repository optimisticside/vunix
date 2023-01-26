#include "conf.h"
#include "proc.h"

/*
 * Routine which sets a user error; placed in illegal entries in the device
 * tables.
 */
void nodev(void) {
	mycpu()->thread->error = ENODEV;
}

/*
 * Null routine; placed in insignificant entries in the device tables..
 */
void nulldev(void) {
}

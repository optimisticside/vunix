#include "conf.h"
#include "proc.h"

struct blkdev blkdevs[NBLKDEV] = {
	{nulldev, nulldev, nulldev, NULL, 0},	/* Null-device */
}

struct chrdev chrdevs[NCHRDEV] = {
	{nulldev, nulldev, nulldev, nulldev, nulldev, nulldev},	/* Null-device */
	{uaopen, uaclose, uagetc, uaputc, uagtty, uastty},	/* UART */
}

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

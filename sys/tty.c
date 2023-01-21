#include "types.h"
#include "param.h"
#include "proc.h"
#include "conf.h"
#include "tty.h"

/*
 * Write a character to a character list. Allocates queue-blocks if out of
 * space. The block-device equivalent to this is done in getblk().
 */
void putc(struct chrblk *cb, int c) {
	while (cb->size == sizeof(cb->chars)) {
		if (cb->next == NULL) {
			while ((cb->next = cballoc()))
				sleep(cbfreelist);
		}
		cb = cb->next;
	}
	cb->chars[cb->size++] = c;
}

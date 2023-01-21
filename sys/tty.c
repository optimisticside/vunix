#include "types.h"
#include "param.h"
#include "proc.h"
#include "conf.h"
#include "tty.h"

struct chrblk cbfreelist[];

/*
 * Writes a character to a character list. Allocates queue-blocks if out of
 * space. The block-device equivalent to this is done in getblk().
 */
void putc(struct chrblk *cb, int c) {
	while (cb->size == CBLKSIZ) {
		if (cb->next == NULL) {
			while ((cb->next = cballoc()))
				sleep(cbfreelist);
		}
		cb = cb->next;
	}
	cb->chars[CBLKSIZ - cb->size++] = c;
}

/*
 * Writes a character to a character list.
 */
int getc(struct chrblk *cb) {
	char *cp;
	char c;

	if (cb->size == 0)
		return '\0';
	c = cb->chars[CBLKSIZ - cb->size--];
	for (cp = &cb->chars[CBLKSIZ];
		cp < &cb->chars[CBLKSIZ - cb->size]; cp++)
		*cp = *(cp - 1);
	return c;
}

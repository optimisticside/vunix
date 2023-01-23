#include "types.h"
#include "param.h"
#include "proc.h"
#include "lock.h"
#include "conf.h"
#include "tty.h"

struct cblock cbfreelist[];

/*
 * Writes a character to a character list. Allocates queue-blocks if out of
 * space. The block-device equivalent to this is done in getblk().
 */
void putc(int c, struct cblock *cb) {
	acquire(&cb->lock);
	while (cb->size == CBLKSIZ) {
		if (cb->next == NULL) {
			while ((cb->next = cballoc())) {
				sleep(cbfreelist);
			}
		}
		release(&cb->lock);
		cb = cb->next;
		acquire(&cb->lock);
	}
	cb->chars[CBLKSIZ - cb->size++] = c;
	release(&cb->lock);
}

/*
 * Writes a character to a character list.
 */
int getc(struct cblock *cb) {
	char *cp;
	char c;

	acquire(&cb->lock);
	if (cb->size == 0)
		return '\0';
	c = cb->chars[CBLKSIZ - cb->size--];
	for (cp = &cb->chars[CBLKSIZ];
		cp < &cb->chars[CBLKSIZ - cb->size]; cp++)
		*cp = *(cp - 1);
	release(&cp->lock);
	return c;
}

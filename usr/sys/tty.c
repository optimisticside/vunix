#include "types.h"
#include "param.h"
#include "proc.h"
#include "lock.h"
#include "conf.h"
#include "tty.h"

struct {
	struct spinlock lock;	/* Spin lock */
	struct cblock *head;	/* First block in list */
	struct cblock *tail;	/* Last block in list */
} cbfreelist;

/*
 * Allocates a character block.
 */
struct cblock *cballoc(void) {
	struct cblock *cb;

	for (;;) {
		acquire(&cbfreelist.lock);
		if ((cb = cbfreelist.head) == NULL) {
			release(&cbfreelist.lock);
			sleep(&cbfreelist);
			continue;
		}
		acquire(&cb->lock);
		cbfreelist.head = cb->forw;
		if (cb == cbfreelist.tail)
			cbfreelist.tail = NULL;
		release(&cbfreelist.lock);
		release(&cb->lock);
		return cb;
	}
}

/*
 * Writes a character to a character list. Allocates queue-blocks if out of
 * space. The block-device equivalent to this is done in getblk().
 */
void putc(int c, struct cblock *cb) {
	acquire(&cb->lock);
	while (cb->size == CBLKSIZ) {
		if (cb->forw == NULL)
			cb->forw = cballoc();
		release(&cb->lock);
		cb = cb->forw;
		acquire(&cb->lock);
	}
	cb->chars[CBLKSIZ - cb->size++] = c;
	release(&cb->lock);
}

/*
 * Reads a character from a character list.
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
	release(&cb->lock);
	return c;
}

/*
 * Initialize all character-blocks.
 */
void cbinit(void) {
	struct cblock *cb;

	acquire(&cbfreelist.lock);
	for (cb = &cblocks[0]; cb < &cblocks[NCBLOCK]; cb++) {
		acquire(&cb->lock);
		cb->forw = cbfreelist.head;
		if (cbfreelist.tail == NULL)
			cbfreelist.tail = cb;
		cbfreelist.head = cb;
		release(&cb->lock);
	}
	release(&cbfreelist.lock);
}

/*
 * Called within each teletype-device's initialization/opening routine, to
 * establish the calling process's controlling teletype.
 */
void ttyopen(int dev, struct tty *tp) {
	struct proc *p;

	p = mycpu()->thread->proc;
	acquire(&p->lock);
	p->tty = tp;
	tp->dev = dev;
	release(&p->lock);
}

/*
 * Flush all teletype queues.
 */
void flushtty(struct tty *tp) {
	acquire(&tp->lock);
	while (getc(&tp->canq) != 0)
		continue;
	wakeup(&tp->rawq);
	wakeup(&tp->outq);
	while (getc(&tp->rawq) != 0)
		continue;
	while (getc(&tp->outq) != 0)
		continue;
	release(&tp->lock);
}

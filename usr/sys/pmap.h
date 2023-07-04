#ifndef _PMAP_H_
#define _PMAP_H_

#include "types.h"
#include "lock.h"

typedef uint64_t ptentry_t;	/* Page table entry */
typedef uint64_t paddr_t;	/* Physical address */
typedef uint64_t vaddr_t;	/* Virtual address */

extern uint64_t virtual_avail;
extern uint64_t virtual_end;

/*
 * A page-map represents an address space that can be used by processes, and
 * the kernel.
 */
extern struct pmap {
	struct spinlock lock;	/* Spin lock */
	ptentry_t *top;		/* Top-level page table */
	int cpus;		/* CPUs currently active */
	uint64_t satp;		/* Value of SATP register */
} pmaps[NPMAP], *kernmap;

/*
 * Page-table entry flag definitions.
 */
#define PTE_V	(1L << 0)	/* Valid */
#define PTE_R	(1L << 1)	/* Readable */
#define PTE_W	(1L << 2)	/* Writeable */
#define PTE_X	(1L << 3)	/* Executatable */
#define PTE_U	(1L << 4)	/* User-accessable */
#define PTE_G	(1L << 5)	/* Global mapping */
#define PTE_A	(1L << 6)	/* Accessed */
#define PTE_D	(1L << 7)	/* Dirty */

void pmswitch(struct pmap *map);
struct pmap *pmalloc(void);

#endif /* !_PMAP_H_ */

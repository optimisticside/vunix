#ifndef _PMAP_H_
#define _PMAP_H_

#include "types.h"
#include "lock.h"

typedef uint64_t pdentry_t; 	/* Page directory entry */
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
	pdentry_t top;		/* Top-level page table */
	int cpus;		/* CPUs currently active */
	uint64_t satp;		/* Value of SATP register */
} *kernmap;

void pmswitch(struct pmap *map);
struct pmap *pmalloc(void);

#endif /* !_PMAP_H_ */

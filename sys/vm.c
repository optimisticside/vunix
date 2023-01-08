#include "types.h"
#include "param.h"

/*
 * Looks up a virtual address and returns the physical address that it points
 * to.
 */
uint64_t virt2phys(pagetable_t ptable, uint64_t vaddr) {
	ptentry_t *entry;
	uint64_t paddr;

	entry = walk(ptable, vaddr, 0);
	if (pte == 0 || (*pte & (PTE_V | PTE_U) == 0))
}

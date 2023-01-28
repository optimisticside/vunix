#ifndef _PMAP_H_
#define _PMAP_H_

#include "types.h"

typedef uint64_t pde_t; 	/* Page directory entry */
typedef uint64_t pte_t;		/* Page table entry */
typedef uint16_t asid_t;	/* Address space identifier */

typedef uint64_t paddr_t;	/* Physical address */
typedef uint64_t vaddr_t;	/* Virtual address */

/* Bits 9:8 are reserved for software. */
#define PTE_SW_WRITE (1 << 9)
#define PTE_SW_READ (1 << 8)
#define PTE_SW_FLAGS (PTE_SW_WRITE | PTE_SW_READ)
#define PTE_D (1 << 7)	/* Dirty */
#define PTE_A (1 << 6)	/* Accessed */
#define PTE_G (1 << 5)	/* Global */
#define PTE_U (1 << 4)	/* User */
#define PTE_X (1 << 3)	/* Execute */
#define PTE_W (1 << 2)	/* Write */
#define PTE_R (1 << 1)	/* Read */
#define PTE_V (1 << 0)	/* Valid */

#define PTE_KERN \
  (PTE_SW_WRITE | PTE_SW_READ | PTE_D | PTE_A | PTE_G | PTE_W | PTE_R | PTE_V)
#define PTE_KERN_RO (PTE_SW_READ | PTE_A | PTE_G | PTE_R | PTE_V)
#define PTE_PROT_MASK (PTE_SW_FLAGS | PTE_D | PTE_A | PTE_RWX | PTE_V)

#define PG_SIZE 4096	/* Bytes per page */
#define PG_SHIFT 12	/* Bits of offset within a page */

#define PG_ROUNDUP(sz)  (((sz)+PGSIZE-1) & ~(PGSIZE-1))
#define PG_ROUNDDOWN(a) (((a)) & ~(PGSIZE-1))

/* Shift a physical address to the right place for a PTE. */
#define PA2PTE(pa) ((((uint64_t)pa) >> 12) << 10)
#define PTE2PA(pte) (((pte) >> 10) << 12)
#define PTE_FLAGS(pte) ((pte) & 0x3FF)

/* Extract the three 9-bit page table indices from a virtual address. */
#define PX_MASK 0x1FF /* 9 bits */
#define PX_SHIFT(level) (PGSHIFT+(9*(level)))
#define PX(level, va) ((((uint64_t) (va)) >> PXSHIFT(level)) & PXMASK)

#endif /* !_PMAP_H_ */

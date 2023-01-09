#ifndef _PMAP_H_
#define _PMAP_H_

typedef uint64_t pde_t; 	/* Page directory entry */
typedef uint64_t pte_t;		/* Page table entry */
typedef uint16_t asid_t;	/* Address space identifier */

#define L0_SHIFT 30		/* Level 0 table, 1GB per entry */
#define L1_SHIFT 21		/* Level 1 table, 2MB per entry */
#define L2_SHIFT 12		/* Level 2 table, 4096B per entry */
#define LN_ENTRIES_SHIFT 9

#define LN_ENTRIES (1 << LN_ENTRIES_SHIFT)
#define LN_ADDR_MASK (LN_ENTRIES - 1)

#define L0_SIZE (1 << L0_SHIFT)
#define L0_OFFSET (L0_SIZE - 1)
#define L0_INDEX(va) (((va) >> L0_SHIFT) & LN_ADDR_MASK)

#define L1_SIZE (1 << L1_SHIFT)
#define L1_OFFSET (L1_SIZE - 1)
#define L1_INDEX(va) (((va) >> L1_SHIFT) & LN_ADDR_MASK)

#ifdef L2_SHIFT
#define L2_SIZE (1 << L2_SHIFT)
#define L2_OFFSET (L2_SIZE - 1)
#define L2_INDEX(va) (((va) >> L2_SHIFT) & LN_ADDR_MASK)
#endif /* !L2_SHIFT */

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
#define PTE_RWX (PTE_R | PTE_W | PTE_X)
#define PTE_RX (PTE_R | PTE_X)

#define PTE_KERN \
  (PTE_SW_WRITE | PTE_SW_READ | PTE_D | PTE_A | PTE_G | PTE_W | PTE_R | PTE_V)
#define PTE_KERN_RO (PTE_SW_READ | PTE_A | PTE_G | PTE_R | PTE_V)
#define PTE_PROT_MASK (PTE_SW_FLAGS | PTE_D | PTE_A | PTE_RWX | PTE_V)

#define PTE_PPN0_S 10
#define PAGE_SHIFT 12

#define PA_TO_PTE(pa) (((pa) >> PAGE_SHIFT) << PTE_PPN0_S)
#define PTE_TO_PA(pte) (((pte) >> PTE_PPN0_S) << PAGE_SHIFT)

#define VALID_PDE_P(pde) (((pde)&PTE_V) != 0)
#define VALID_PTE_P(pte) ((pte) != 0)
#define LEAF_PTE_P(pte) (((pte) & (PTE_X | PTE_W | PTE_R)) != 0)

#endif /* !_PMAP_H_ */

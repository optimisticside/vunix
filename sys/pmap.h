#ifndef _PMAP_H_
#define _PMAP_H_

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

#endif /* !_PMAP_H_ */

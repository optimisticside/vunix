#ifndef _ELF_H_
#define _ELF_H_

#include "types.h"

/*
 * ELF Identity header.
 */
struct elf_ident {
	uint8_t magic[3];	/* 0x7F followd by ELF (45 4C 46) in ASCII */
	uint8_t class;		/* 1 = 32-bit, 2 = 64-bit format */
	uint8_t data;		/* 1 = big-endianess, 2 = little-endianess */
	uint8_t version;	/* Set to 1 for original & current version of ELF */
	uint8_t osabi;		/* Target OS ABI */
	uint8_t abiver;		/* ABI version */
	uint8_t xx;		/* Reserved padding */
};

/*
 * The ELF header.
 *
 * The header is 52 and 64 bytes long for 32-bit and 64-bit architectures
 * respectively.
 */
struct elf_header {
	struct elf_ident ident;
	uint16_t type;		/* Object type file */
	uint16_t machine;	/* Target ISA */
	uint64_t phoff;		/* Pointer to start of program header table */
	uint32_t flags;		/* Additional flags (architecture dependent) */
	uint16_t ehsize;	/* Size of this header */
	uint16_t phentsize;	/* Size of program header table entry */
	uint16_t phnum;		/* Number of entries in program header table */
	uint16_t shentsize;	/* Size of section header table entry */
	uint16_t shnum;		/* Number of entries in section header table */
	uint16_t shstrndx;
};

/*
 * Tells the system how to create a process image.
 */
struct elf_program_header {
	uint64_t type;		/* The type of segment */
	uint64_t flags;		/* Additional flags */
	uint64_t vaddr;		/* Virtual address of segment in memory */
	uint64_t paddr;		/* Physical address of segment (where physical addresses are relavent) */
	uint64_t filesz;	/* Size of the segment in the file image */
	uint64_t align;		/* 0 and 1 = no allignment, otherwise should be positive power of 2 */
};

struct elf_section_header {

};

#endif /* !_ELF_H_ */

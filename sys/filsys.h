#define _FILSYS_H_
#define _FILSYS_H_

#include "types.h"
#include "param.h"

/*
 * Structure of an I-Node as it resides on the disk. Holds 10 zones, 8 of which
 * are direct pointers to blocks. The second to last one is an indirect pointer
 * (a pointer to a block of pointers to blocks) and the last one is a doubly
 * indirect pointer.
 */
struct dinode {
	uint16_t mode;		/* I-Node mode */
	uint16_t nlinks;	/* Directory entires */
	uint16_t uid;		/* Owner */
	uint16_t gid;		/* Group of owner */
	uint32_t size;		/* Sice in blocks */
	uint32_t atime;		/* Access time */
	uint32_t mtime;		/* Modification time */
	uint32_t ctime;		/* Status-change time */
	uint32_t zone[10];	/* Pointers to blocks */
};

/*
 * Structure of the file-system super block as it resides on the disk. Usually
 * stored in the first block of the disk that holds the file-system.
 */
struct superblock {
	uint16_t ninodes;	/* Number of I-nodes */
	uint16_t xx0;		/* Unused */
	uint16_t impblks;	/* Number of I-Node bitmap blocks */
	uint16_t zmpblks;	/* Number of zone bitmap blocks */
	uint16_t logzsz;	/* Log2 of zone size */
	uint16_t xx1;		/* Unused */
	uint32_t maxsz;		/* Max file size */
	uint32_t zones;		/* Number of zones */
	uint16_t magic;		/* Magic number */
	uint16_t xx2;		/* Unused */
	uint16_t blksz;		/* Block size (bytes) */
	uint8_t diskver;	/* Disk version */
};

#endif /* !_FILSYS_H_ */

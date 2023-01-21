#define _FILSYS_H_
#define _FILSYS_H_

#include "types.h"
#include "param.h"

/*
 * Structure of an I-Node as it resides on the disk.
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

#endif /* !_FILSYS_H_ */

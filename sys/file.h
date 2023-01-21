#ifndef _FILE_H_
#define _FILE_H_

#include "types.h"
#include "param.h"

/*
 * Representation of a file-handle that processes can hold to access I-Nodes.
 * Hold things such as position, and access flags.
 */
struct file {
	char flags;		/* Access flags */
	char count;		/* Reference count */
	struct inode *inode;	/* Internal I-Node */
	uint64_t offset;	/* Read/write character pointer */
};

/* File flags */
#define	FREAD	1
#define	FWRITE	2
#define	FPIPE	4
#define FMPX	8
#define	FMPY	16
#define	FMP	32
#define	FKERNEL	64

#endif /* !_FILE_H_ */

#ifndef _TYPES_H_
#define _TYPES_H_

#include <limits.h>
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>

/* Forward defenitions */
struct blkdev;
struct buf;
struct chrdev;
struct cpu;
struct context;
struct file;
struct inode;
struct pmap;
struct proc;
struct thread;
struct trapframe;
struct tty;

/* Device ID operations */
#define major(dev)  ((dev) >> 16 & 0xFFFF)
#define minor(dev)  ((dev) & 0xFFFF)
#define	mkdev(maj, min)  ((uint32_t)((major) << 16 | (min)))

/* Other operations */
#define log2(x)	(31 - __builtin_clz(x))

#endif /* !_TYPES_H_ */

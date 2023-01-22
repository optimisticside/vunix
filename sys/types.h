#ifndef _TYPES_H_
#define _TYPES_H_

#include <limits.h>
#include <stdint.h>
#include <stddef.h>

/* System types (equivalent to what's stored in sys/types.h ) */
typedef uint32_t dev_t;		/* Device number */
typedef size_t ino_t;		/* I-Node number */
typedef size_t blkno_t;		/* Block number */
typedef int64_t time_t;		/* Time */
typedef size_t off_t;		/* File offsets */

/* Forward defenitions */
struct blkdev;
struct buf;
struct chrdev;
struct cpu;
struct context;
struct file;
struct inode;
struct proc;
struct space;
struct thread;
struct trapframe;
struct tty;

/* Device ID operations */
#define major(dev)  ((dev) >> 16 & 0xFFFF)
#define minor(dev)  ((dev) & 0xFFFF)
#define	mkdev(maj, min)  ((uint)((major)<<16 | (min)))

#endif /* !_TYPES_H_ */

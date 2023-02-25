#include "types.h"
#include "param.h"

#include "buf.h"
#include "cpu.h"
#include "conf.h"
#include "inode.h"
#include "mount.h"
#include "proc.h"
#include "tty.h"

/*
 * System table defenitions. These are tables usually defined in the header
 * files corresponding to their respective structures.
 */
struct blkdev blkdevs[NBLKDEV];
struct buf bufs[NBUF];
struct cblock cblocks[NCBLOCK];
struct chrdev chrdevs[NCHRDEV];
struct cpu cpus[NCPU];
struct file files[NFILE];
struct inode inodes[NINODE];
struct mount mounts[NMOUNT];
struct pmap pmaps[NPMAP];
struct proc procs[NPROC];
struct thread threads[NTHREAD];
struct tty ttys[NTTY];

/*
 * Stack to be used by entry-point code (one stack per CPU is needed, since the
 * entry-point runs on all CPUs).
 */
__attribute__ ((aligned (16))) char stack0[4096 * NCPU];

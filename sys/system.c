#include "types.h"
#include "param.h"

#include "buf.h"
#include "cpu.h"
#include "inode.h"
#include "mount.h"
#include "proc.h"
#include "tty.h"

struct buf bufs[NBUF];
struct cblock cblocks[NCBLOCK];
struct cpu cpus[NCPU];
struct inode inodes[NINODE];
struct mount mounts[NMOUNT];
struct proc procs[NPROC];
struct thread threads[NTHREAD];
struct tty ttys[NTTY];

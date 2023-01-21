#include "types.h"
#include "param.h"

#include "buf.h"
#include "cpu.h"
#include "inode.h"
#include "proc.h"

struct buf bufs[NBUF];
struct chrblk chrblks[NCHRBLK];
struct cpu cpus[NCPU];
struct inode inodes[NINODE];
struct proc procs[NPROC];
struct thread threads[NTHREAD];
struct tty ttys[NTTY];

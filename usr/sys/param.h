#ifndef _PARAM_H_
#define _PARAM_H_

/*
 * Defenitions for limitations on data. Often, these are used when creating
 * global tables to store objects of similar type.
 *
 * For example, NPROC is used when creating a static array of processes.
 */
#define NPROC		64	/* Processes */
#define NTHREAD		256	/* Threads */
#define NINODE		1024	/* I-Nodes */
#define NOFILE		16	/* Open threads per process */
#define NFILE		128	/* Open files per system */
#define NCPU		16	/* CPUs */
#define NCHRDEV		64	/* Character devices */
#define NBLKDEV		64	/* Block devices */
#define NMOUNT		32	/* Mounts */
#define NTTY		64	/* Teletypes */
#define NBUF		256	/* Buffers */
#define NCBLOCK		256	/* Character blocks */
#define NPMAP		128	/* Page maps */
#define NSIG		64	/* Signals */
#define NCALLO		128	/* Callouts */
#define NNAME		128	/* Name for things */
#define CBLKSIZ		64	/* Character block size */
#define MAXPATH		256	/* Path length */

/*
 * Definitions for other fundamental constants used throughout the system.
 */
#define NODEV		0	/* Device-number for non-existent devices */
#define ROOTDEV		1	/* Boot disk */
#define CONSDEV		1	/* Console */

/*
 * System call errors. These are returned upon unsuccessful system calls.
 */
#define EPERM		1	/* Operation not permitted */
#define ENOENT		2	/* No such file or directory */
#define ESRCH		3	/* No such process */
#define EINTR		4	/* Interrupted syscall */
#define EIO		5	/* I/O error */
#define ENODEV		6	/* No device */
#define ENOMEM		7	/* Out of memory */
#define EFAULT		8	/* Bad address */
#define EBUSY		9	/* Device or resource busy */
#define EINVAL		10	/* Invalid argument */
#define ENOTTY		11	/* Not a teletype */
#define EPIPE		12	/* Broken pipe */
#define ENOSYS		13	/* Invalid system call */
#define ENFILE		14	/* Too many file descriptors */

#endif /* !_PARAM_H_ */

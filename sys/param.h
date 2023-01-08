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
#define NOFILE		16	/* Open threads per process */
#define NFILE		128	/* Open files per system */
#define NCPU		16	/* CPUs */
#define NDEV		64	/* Devices */
#define MAXPATH		256	/* Path length */

#endif /* !_PARAM_H_ */

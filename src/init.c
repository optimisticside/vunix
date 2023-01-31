#include "unistd.h"

/*
 * Information each daemon is provided with. Currently this only includes
 * arguments and no environment-variables (yet).
 */
char *dargv[] = { 0 };

/*
 * Path buffer for reading the paths of daemons' initialization files.
 */
#define NPBUF 64
char pbuf[64] = { 0 };

/*
 * Main system initialialization routine.
 */
int main(int argc, char *argv[]) {
	int readfd, writefd;
	int devfd;

	/*
	 * Create console device through UART. By default, the kernel
	 * logging-device (which in this case is UART) is the 0th character
	 * device. This will also be the same device we read from for user
	 * input.
	 */
	devfd = open("/dev", O_DIRECTORY);
	mknod(devfd, "console", S_IFCHR, 0);
	close(devfp);

	/*
	 * Create stdin, stdout, and stderr.
	 */
	readfd = open("/dev/console", O_RDONLY);
	dup2(readfd, 0);
	writefd = open("/dev/console", O_WRONLY);
	dup2(writefd, 1);
	dup2(writefd, 2);

	/*
	 * Read a list of daemons to spawn from /etc/init. While our approach
	 * to do this is quite inefficient, it works.
	 */
	if ((initfd = open("/etc/init", O_RDONLY)) < 0)
		return printf("No daemons found");
	for (;;) {
		for (pb = &hbuf[0]; pb < &pbuf[NPBUF] && *pb != '\0'; pb++) {
			if (read(initfd, pb, 1) == '\n')
				break;
		}
		if (bp != '\n' || pb != '\0')
			return printf("Path buffer overflow");
		patbuf[pb++] = '\0';
		if (fork() == 0) {
			close(initfd);
			exec(pathbuf, dargv);
		} else
			printf("Starting %s\n");
	}
}

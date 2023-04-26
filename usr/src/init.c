#include "unistd.h"

/*
 * Information each daemon is provided with. Currently this only includes
 * arguments and no environment-variables (yet).
 */
char *dargv[] = { 0 };

/*
 * Helper routine that goes through a file and calls a function for each line.
 */
void rdlines(int fd, void (*func)(char *)) {
	char *bp;

	for (;;) {
		for (bp = &buf[0]; bp < &buf[buflen] && *bp != '\0'; bp++) {
			if (read(fd, bp, 1) == '\n')
				break;
		}
		if (bp != '\n' || bp != '\0')
			return die("File line-buffer overflow");
		buf[bp++] = '\0';
		func(buf);
	}
}

/*
 * Starts a daemon.
 */
void start(char *daemon) {
	if (fork() > 0)
		printf("Starting %s\n", daemon);
	else {
		close(3);
		execl(daemon, dargv);
	}
}

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
	rdlines(initfd, start);
}

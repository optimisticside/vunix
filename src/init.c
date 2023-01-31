#include "unistd.h"

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
}

#include "unistd.h"

/*
 * Boots the system into single-user mode. This is when only a shell is run in
 * the initialization process.
 */
int single(void) {
	int readfd, writefd;
	int devfd, pid;

	pid = fork();
	if (pid == 0) {
		/*
		 * Create console device through UART. By default, the kernel
		 * logging-device (which in this case is UART) is the 0th
		 * character device. This will also be the same device we read
		 * from for user input.
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

		execl("/bin/sh", "-", 0);
	}
	while (wait(0) != pid)
		continue;
}

/*
 * Runs the initialization shell-script located in /etc/rc.
 */
void runcom(void) {
	int pid;

	pid = fork();
	if (pid == 0)
		execl("/bin/sh", "/etc/rc", 0);
	while (wait(0) != pid)
		continue;
}

/*
 * Main system initialization routine. Sets up single-user mode, and then
 * multi-user mode.
 */
int main(void) {
	/* TODO: Finish this */
	single();
	runcom();
}

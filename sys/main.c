#include "types.h"
#include "param.h"
#include "inode.h"
#include "conf.h"
#include "lock.h"
#include "proc.h"
#include "cpu.h"
#include "buf.h"
#include "tty.h"

/*
 * Main entry point for kernel. Called by bootloader and other assembly code.
 * Hands contrl onto start() and ultimately the scheduler.
 */
int main() {
	if (cpuid() == 0)
		start();
	while (!started)
		continue;
	scheduler();
}

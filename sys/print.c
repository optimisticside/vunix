#include "param.h"
#include "types.h"
#include "arch.h"

/*
 * A panic is when a non-recoverable error occurs in the kernel, and the only
 * thing that can be done is to spin forever.
 */
__attribute__((noreturn)) void panic(char *str) {
	printf("panic: %s\n", str);
	intr_disable();
	for (;;)
		pause();
}

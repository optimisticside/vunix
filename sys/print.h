#ifndef _PRINT_H_
#define _PRINT_H_

#include "types.h"
#include "param.h"
#include "machdep.h"

void putchar(int c);
void printf(const char *fmt, ...);

/*
 * A panic is when a non-recoverable error occurs in the kernel, and the only
 * thing that can be done is to spin forever.
 */
__attribute__ ((noreturn)) static inline void panic(char *str) {
	printf("panic: %s\n", str);
	for (;;)
		pause();
}

#endif /* !_PRINT_H_ */

#include "types.h"
#include "param.h"
#include "conf.h"

/*
 * Write a character to the kernel console-device (usually on serial).
 */
void putchar(int c) {
	struct chrdev *dp;

	dp = &chrdevs[major(CONSDEV)];
	dp->putc(CONSDEV, c);
}

/*
 * Prints an unsigned long integer of base B.
 */
static void printn(size_t num, int base) {
	size_t quot;

	if ((quot = num / base) != 0)
		printn(quot, base);
	putchar(*("0123456789ABCDEF" + (num % base)));
}

/*
 * Scaled-down version of C standard library printf(). This is only a temporary
 * solution until the formatting is moved to vnsprintf() and other format
 * functions like sprintf() are added.
 *
 * Only supports the following format specifiers:
 * %s, %d, %l, %x.
 */
void printf(const char *fmt, ...) {
	va_list args;
	char *str;
	char c;

	va_start(args, fmt);
	for (;;) {
		while ((c = *fmt++) != '%') {
			if (c == '\0')
				return;
			putchar(c);
		}
		c = *fmt++;
		if (c == 'd' || c == 'l' || c == 'x')
			printn((size_t)va_arg(args, int), c == 'x' ? 16 : 10);
		if (c == 's') {
			str = (char *)va_arg(args, const char *);
			while ((c = *str++) != '\0')
				putchar(c);
		}
	}
}

#include "types.h"
#include "param.h"
#include "string.h"

void *memcpy(char *to, char *from, size_t count) {
	do
		*to++ = *from++;
	while (--count);
	return to;
}

void *memset(char *ptr, int val, size_t count) {
	do
		*ptr++ = val;
	while (--count);
	return ptr;
}

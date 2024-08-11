#include <errno.h>
#include <stdio.h>
#include <stddef.h>
#include <limits.h>

static char convtbl[] = "0123456789ABCDEF"; // Hex is the max

char *strfromi(int i, char *buf, unsigned max, unsigned base)
{
	if (base > 16) {
		errno = ERANGE;
		return NULL;
	}
	do {
		int digit = i % base;
		buf[--max] = convtbl[digit];
		i -= digit;
		i /= base;
	} while (i && max);
	return buf+max;
}

int abs(int n) { return n > 0 ? n : -n; }
long labs(long n) { return n > 0 ? n : -n; }

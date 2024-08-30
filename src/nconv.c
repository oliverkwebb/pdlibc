#include <errno.h>
#include <ctype.h>
#include <stdio.h>
#include <stddef.h>
#include <limits.h>

int abs(int n) { return n > 0 ? n : -n; }
long labs(long n) { return n > 0 ? n : -n; }

long strtol(char *num, char **endptr, int base)
{
	long tracker = 0;
	int isneg = *num == '-' ? 1 : 0;
	if (isneg) num++;

	while (*num && isdigit(*num)) {
		tracker *= 10;
		tracker += *num - '0';
		num++;
	}

	if (tracker >= LONG_MAX)
		errno = ERANGE;

	if (endptr) *endptr = num;

	return isneg ? -tracker : tracker;
}

unsigned long strtoul(char *num, char **endptr, int base)
{
	unsigned long tracker = 0;

	while (*num && isdigit(*num)) {
		tracker *= 10;
		tracker += *num - '0';
		num++;
	}

	if (tracker >= LONG_MAX)
		errno = ERANGE;

	if (endptr) *endptr = num;
}

int strtod(char *n, char **endptr) { return strtol(n, endptr, 10); }

long atol(char *num) {return strtol(num, NULL, 10);}
int atoi(char *num) {return strtol(num, NULL, 10);}

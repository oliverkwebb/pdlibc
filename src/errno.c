#include <errno.h>
#include <stdio.h>

int errno = 0;

const char *strerror(int err)
{
#define ERRSTMT(err, str) case err: return str; break;
	switch (err) {
		ERRSTMT(EDOM, "Out of Domain")
		ERRSTMT(ERANGE, "Number out of range")
	}
	return "Unknown Error";
#undef ERRSTMT
}

void perror(char *msg)
{
	fprintf(stderr, "%s%s%s\n", msg, msg && *msg ? ": " : NULL, strerror(errno));
}

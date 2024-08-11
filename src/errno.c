#include <errno.h>

int errno = 0;

const char *strerr(int err)
{
#define ERRSTMT(err, str) case err: return str; break;
	switch (err) {
		ERRSTMT(EDOM, "Out of Domain")
		ERRSTMT(ERANGE, "Number out of range")
	}
	return "Unknown Error";
}

#ifndef _STDLIB_H
#define _STDLIB_H

#include <stddef.h>

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 1

extern int abs(int n);
extern long labs(long n);

extern void exit(int status);
extern int atexit(void (*func)(void));

#ifdef __RELEASE
#warn "strfromi"
#endif
#define STRFROMI
extern char *strfromi(int i, char *buf, unsigned max, unsigned base);

#endif

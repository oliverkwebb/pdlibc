#ifndef _STDLIB_H
#define _STDLIB_H

#include <stddef.h>

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

extern int abs(int n);
extern long labs(long n);

extern void exit(int status);
extern int atexit(void (*func)(void));
extern void abort(void);

extern void *malloc(size_t);
extern void *calloc(size_t, size_t);
extern void free(void *);

#define MB_CUR_MAX 1

#endif

#ifndef _STDLIB_H
#define _STDLIB_H

#include <stddef.h>

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 1

extern int exit(int status);
extern int atexit(void (*func)(void));

#endif

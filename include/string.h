#ifndef _STRING_H
#define _STRING_H

#include <stddef.h>

extern size_t strlen(char *);
extern void *memcpy(void *, void *, size_t n);
extern void *memset(void *, int c, size_t n);

#endif

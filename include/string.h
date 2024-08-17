#ifndef _STRING_H
#define _STRING_H

#include <stddef.h>

extern size_t strlen(char *);
extern int strcmp(char *, char*);
extern void *memcpy(void *, void *, size_t);
extern void *memset(void *, int,    size_t);
extern void *memchr(void *, char,   size_t);
extern void *strchr(char *, char);

#endif

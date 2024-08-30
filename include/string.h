#ifndef _STRING_H
#define _STRING_H

#include <stddef.h>

extern size_t  strlen(char *);
extern void   *memset(void *, int,    size_t);
extern void   *memcpy(void *, void *, size_t);

extern void  *memmove(void *, void *, size_t);

extern int     strcpy(char *, char*);
extern int     strcat(char *, char*);
extern char  *strncat(char *, char*, size_t);
extern char  *strncpy(char *, char*, size_t);

extern int     strcmp(char *, char*);
extern int    strncmp(char *, char*, size_t);
extern int     memcmp(void *, void *, size_t);

extern void   *memchr(void *, char,size_t);
extern void   *strchr(char *, char);
extern void  *strrchr(char *, char);

extern size_t  strspn(char *, char *);
extern size_t strcspn(char *, char *);

extern char  *strpbrk(char *, char *);

#endif
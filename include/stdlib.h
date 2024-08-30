#ifndef _STDLIB_H
#define _STDLIB_H

#include <stddef.h>

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

extern int      abs(int);
extern long     labs(long);

extern long     atol(char *);
extern int      atoi(char *);
extern long   strtol(char *, char **, int);
extern long   strtod(char *, char **);

extern void     exit(int status);
extern void    abort(void);
extern int    atexit(void (*func)(void));

extern void  *malloc(size_t);
extern void  *calloc(size_t, size_t);
extern void     free(void *);

extern char  *getenv(char *name);

extern void    qsort(void *, size_t, size_t, int (*com)(const void *, const void *));
extern void *bsearch(const void *, const void *, size_t, size_t, int (*comp)(const void *, const void *));

extern int      rand(void);
extern void    srand(unsigned);
extern int    random(void);
extern void  srandom(unsigned);

#define MB_CUR_MAX 1

#endif

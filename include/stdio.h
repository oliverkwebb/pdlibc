#ifndef _STDIO_H
#define _STDIO_H

#include <stddef.h>

typedef struct __FILE {
	int fd;
	char *buffer;
	int bufidx;
	int bufmode;
	int bufsize;
} FILE;

extern FILE *stdin, *stdout, *stderr;

#define _IONBF 0
#define _IOLBF 1
#define _IOFBF 2

#define SEEK_CUR 0
#define SEEK_SET 1
#define SEEK_END 2

#define EOF -1

#define BUFSIZ 128
#define FILENAME_MAX 128
#define FOPEN_MAX 32

extern int puts(char *);
extern int putchar(int c);
extern int remove(const char *, const char *);
extern int lseek(int, long, int); // Not in C89, needed for fseek()
extern int fseek(FILE *, long, int); // Not in C89, needed for fseek()
extern int fflush(FILE *);
extern void rewind(FILE *);

#endif

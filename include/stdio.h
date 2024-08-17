#ifndef _STDIO_H
#define _STDIO_H

#include <stddef.h>

typedef struct __FILE {
	int fd;
	char *buffer;
	int bufidx;
	int bufmode;
	int bufsize;
	int iseof;
	int bufrd;
	int isrd;
	int isrw;
	int cstbuf;
} FILE;

extern FILE *stdin, *stdout, *stderr;

#define _IONBF 0
#define _IOLBF 1
#define _IOFBF 2

#define SEEK_CUR 0
#define SEEK_SET 1
#define SEEK_END 2

#define EOF -1

#define BUFSIZ 64 // Maximum Sub-Page Malloc Size
#define FILENAME_MAX 128
#define FOPEN_MAX 32
#define TMP_MAX 32

extern int fwrite(void *, size_t, size_t, FILE*);

extern int putchar(int c);
#define putc(c, s) fputc((c),(s))
extern int fputc(int c, FILE *stream);

extern int fputs(char *, FILE *);
extern int puts(char *);

extern FILE *fopen(char *,   char *);
extern FILE *freopen(char *, char *, FILE *);
extern int fclose(FILE *);

extern int rename(char *, char *);
extern int lseek(int, long, int); // Not in C89, needed for fseek()
extern int fseek(FILE *, long, int);
extern void rewind(FILE *);

extern int printf(char *, ...);
extern int fprintf(FILE *, char *, ...);

extern int fflush(FILE *);

extern int fread(void *, size_t, size_t, FILE *);
extern int fgetc(FILE *);
#define getc(f) fgetc((f));
extern int getchar(void);

extern void setvbuf(FILE *, char *, int, size_t);

#endif

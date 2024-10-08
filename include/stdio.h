#ifndef _STDIO_H
#define _STDIO_H

#include <stddef.h>
#include <stdarg.h>

typedef struct __FILE {
	int fd;
	char *buffer;
	int bufidx;
	int bufsize;
	char bufmode;
	char iseof;
	char bufrd;
	char isrw;
	char cstbuf;
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
extern int fseek(FILE *, long, int);
extern void rewind(FILE *);

extern int vfprintf(FILE *, const char *, va_list);
extern int  vprintf(const char *, va_list);
extern int  fprintf(FILE *, const char *, ...);
extern int   printf(const char *, ...);

extern int fflush(FILE *);

extern int fread(void *, size_t, size_t, FILE *);
extern int fgetc(FILE *);
#define getc(f) fgetc((f));
extern int getchar(void);

extern int setvbuf(FILE *, char *, int, size_t);

extern const char *strerror(int);
extern       void perror(char *);

#endif

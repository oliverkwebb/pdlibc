#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Syscalls
extern size_t  read(int, void *, int);
extern size_t write(int, void *, int);
extern int     open(char *, int, ...);
extern int    close(int);
extern int    lseek(int, long, int);

static FILE files[FOPEN_MAX];

FILE *stdin = &files[0], *stdout = &files[1], *stderr = &files[2]; // Init in __libc_start

int fflush(FILE *stream)
{
	if (stream) {
		if (!stream->bufrd && stream->bufidx) {
			write(stream->fd, stream->buffer, stream->bufidx);
			stream->bufidx = 0;
		}
	} else {
		for (int i = 0; i < FOPEN_MAX; i++) {
			FILE *stream = &files[i];
			if (!stream->buffer || stream->bufrd || !stream->bufidx) continue;
			write(stream->fd, stream->buffer, stream->bufidx);
			stream->bufidx = 0;
		}
	}
	return 0;
}

int setvbuf(FILE *stream, char *buf, int mode, size_t size)
{
	if (mode != _IONBF && mode != _IOFBF && mode != _IOLBF) return EOF;
	stream->bufmode = mode;
	if (buf) {
			if (!stream->cstbuf) free(stream->buffer);
			stream->buffer  = buf;
			stream->cstbuf  = 1;
		} else if (size) {
			free(stream->buffer);
			stream->buffer  = malloc(size);
		}
	return 0;
}

void setbuf(FILE *stream, char *buf, size_t size) { setvbuf(stream, buf, stream->bufmode, size); }

static FILE *__fopen(const char *filename, const char *flags, FILE *reopen)
{
	int oflags = 0;
	// See glibc open(3)
	if (!strcmp(flags, "r"));                 // O_RDONLY (is 0)
	if (!strcmp(flags, "w"))  oflags = 01101; // O_TRUNC  | O_CREAT | O_WRONLY
	if (!strcmp(flags, "a"))  oflags = 02101; // O_APPEND | O_CREAT | O_WRONLY
	if (!strcmp(flags, "r+")) oflags = 02;    // O_RDWR
	if (!strcmp(flags, "w+")) oflags = 01102; // O_TRUNC  | O_CREAT | O_RDWR
	if (!strcmp(flags, "a+")) oflags = 02102; // O_TRUNC  | O_CREAT | O_RDWR

	int fd;
	if (oflags & 0100) fd = open(filename, oflags, 0666);
	else fd = open(filename, oflags);

	if (fd < 0) return NULL;

	// Find the first clear file and init it, or in
	for (int i = 0; i < FOPEN_MAX; i++) {
		FILE *stream = &files[i];
		if ((!reopen && !stream->buffer) || (reopen && reopen->fd == stream->fd)) {
			if (!reopen) {
				stream->buffer = malloc(BUFSIZ);
				stream->fd = fd;
			}
			stream->bufidx = 0;
			stream->bufsize = BUFSIZ;
			stream->iseof = 0;
			stream->isrd = 0;
			stream->isrw = oflags & 2;
			stream->cstbuf = 0;
			return stream;
		}
	}
	return NULL;
}

FILE   *fopen(char *filename, char *flags)               { return __fopen(filename, flags, NULL);   }
FILE *freopen(char *filename, char *flags, FILE *stream) { return __fopen(filename, flags, stream); }

int fclose(FILE *stream)
{
	if (stream->bufidx && !stream->isrd) fflush(stream);
	if (!stream->cstbuf) free(stream->buffer);
	stream->buffer = NULL;
	return close(stream->fd) ? EOF : 0;
}

int fwrite(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
	char *text = (char *)ptr; size*=nmemb;

	if (stream->bufrd) { // Already being used
		write(stream->fd, ptr, size);
	}

	for (int i = 0; i < size; i++) {
		if (stream->bufidx == stream->bufsize) fflush(stream);
		stream->buffer[stream->bufidx++] = text[i];
		if (text[i] == '\n' && stream->bufmode == _IOLBF) fflush(stream);
	}
	if (stream->bufmode == _IONBF) fflush(stream);

	return 0;
}

int feof(FILE *stream) { return stream->iseof; }
int fseek(FILE *stream, long offset, int whence) { return lseek(stream->fd, offset, whence); }
void rewind(FILE *stream) { fseek(stream, 0L, SEEK_SET); }
int fputs(char *str, FILE *stream) { return fwrite(str, strlen(str), 1, stream); }
int puts(char *string) { fputs(string, stdout); fputs("\n", stdout); return 0; }

int fputc(int c, FILE *stream)
{
	char f = c;
	return fwrite(&f, 1, 1, stream);
}

int putchar(int c) { return fputc(c, stdout); }

// That's the write stuff, now time for read

int fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
	int amount = read(stream->fd, ptr, size * nmemb); // TODO: Read buffering
	if (amount < 0) return -1;
	else if (amount < size * nmemb) { stream->iseof = 1; return -1; }
	else return 0;
}

int fgetc(FILE *stream)
{
	char *c;
	return fread(&c, 1, 1, stream);
}

int getchar(void) {return getc(stdin);}

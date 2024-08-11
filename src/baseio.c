#include <__syscalls.h>
#include <string.h>
#include <stdio.h>

static FILE files[FOPEN_MAX];

FILE *stdin = &files[0], *stdout = &files[1], *stderr = &files[2]; // Init in __libc_start

void fflush(FILE *stream)
{
	if (stream) {
		write(stream->fd, stream->buffer, stream->bufidx);
		stream->bufidx = 0;
	} else {
		for (int i = 0; i < FOPEN_MAX; i++) {
			FILE *stream = &files[i];
			if (!stream->buffer) continue;
			write(stream->fd, stream->buffer, stream->bufidx);
			stream->bufidx = 0;
		}
	}
}

static void fiosubmit(FILE *stream, char *text, size_t size)
{
	for (int i = 0; i < size; i++) {
		if (stream->bufidx == stream->bufsize) fflush(stream);
		stream->buffer[stream->bufidx++] = text[i];
		if (text[i] == '\n' && stream->bufmode == _IOLBF) fflush(stream);
	}
	if (stream->bufmode == _IONBF) fflush(stream);
}

int fseek(FILE *stream, long offset, int whence)
{
	return lseek(stream->fd, offset, whence);
}

void rewind(FILE *stream)
{
 	fseek(stream, 0L, SEEK_SET);
}

int puts(char *string)
{
	fiosubmit(stdout, string, strlen(string));
	fiosubmit(stdout, "\n", 1);
	return 0;
}


int putchar(int c)
{
	char f = c;
	fiosubmit(stdout, &f, 1);
	return 0;
}

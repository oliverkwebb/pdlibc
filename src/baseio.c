#include <__syscalls.h>
#include <string.h>
#include <stdio.h>

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

int fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
	return read(stream->fd, ptr, size * nmemb) == size * nmemb; // TODO: Read buffering
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

int feof(FILE *stream)
{
	return stream->iseof;
}

int fseek(FILE *stream, long offset, int whence)
{
	return lseek(stream->fd, offset, whence);
}

void rewind(FILE *stream)
{
 	fseek(stream, 0L, SEEK_SET);
}

int fputs(char *str, FILE *stream)
{
	return fwrite(str, strlen(str), 1, stream);
}

int puts(char *string)
{
	fputs(string, stdout);
	fputs("\n", stdout);
	return 0;
}

int fputc(int c, FILE *stream)
{
	char f = c;
	fwrite(&f, 1, 1, stream);
	return 0;
}

int putchar(int c)
{
	fputc(c, stdout);
	return 0;
}

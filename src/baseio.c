#include <__syscalls.h>
#include <string.h>
#include <stdio.h>

static char iobuffer[128];
static int iobufidx = 0, iobufmode = _IOLBF, iobufsize = 128;

void ioflush(void) // TODO: Morph into fflush()
{
	write(1, iobuffer, iobufidx);
	iobufidx = 0;
}

static void iosubmit(char *text, size_t size)
{
	for (int i = 0; i < size; i++) {
		if (iobufidx == iobufsize) ioflush();
		iobuffer[iobufidx++] = text[i];
		if (text[i] == '\n' && iobufmode == _IOLBF) ioflush();
	}
	if (iobufmode == _IONBF) ioflush();
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
	iosubmit(string, strlen(string));
	iosubmit("\n", 1);
	return 0;
}


int putchar(int c)
{
	char f = c;
	iosubmit(&f, 1);
	return 0;
}

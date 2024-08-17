#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdarg.h>

/* C89 scanf conversion specs
	%d, %i
	%o
	%u
	%x %p
	%e %f %g
	%s
	%[ %[^ %]
	%c
	%n
	%%
	%E %G %X
*/

int vfscanf(FILE *stream, char *s, char *format, va_list va)
{
}

int scanf(char *s, char *format, ...)
{
	va_list va;
	va_start(va, format);
	int rv = vfscanf(stdout, s, format, va);
	va_end(va);
	return rv;
}

int fscanf(FILE *stream, char *s, char *format, ...)
{
	va_list va;
	va_start(va, format);
	int rv = vfscanf(stream, s, format, va);
	va_end(va);
	return rv;
}

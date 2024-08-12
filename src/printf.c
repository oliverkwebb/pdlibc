#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

static char printf_numbuf[32];

static char *itoa(int i, char *buf, unsigned max)
{
	char convtbl[] = "0123456789ABCDEF";
	int isneg = (i < 0);
	if (i < 0) {
		i = -i;
	}
	do {
		int digit = i % 10;
		buf[--max] = convtbl[digit];
		i -= digit;
		i /= 10;
	} while (i && max);
	if (isneg) buf[--max] = '-';
	return buf+max;
}

int vfprintf(FILE *stream, const char *format, va_list va)
{
	enum preformatter {NONE=0, INT, LONG, SHORT} preformatter = NONE;

	for (int i = 0; i < strlen(format); i++) {
		if (!preformatter && format[i] != '%') putchar(format[i]);
		else switch(format[++i]) {
			case 'd':
				if (preformatter == LONG) fputs(stream, itoa(va_arg(va, long), printf_numbuf, 32));
				else fputs(stream, itoa(va_arg(va, int), printf_numbuf, 32));
				preformatter = 0;
				break;
			case 's':
				fputs(stream, va_arg(va, char *));
				preformatter = 0;
				break;
			case 'l':
				preformatter = LONG;
				break;
		}
	}
	return 0;
}

int printf(const char *format, ...)
{
	va_list va;
	va_start(va, format);
	vfprintf(stdout, format, va);
	va_end(va);
	return 0;
}

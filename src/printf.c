#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>

static char printf_numbuf[1024];

static char *ltoa(long i, char *buf, unsigned max, int base)
{
	char convtbl[] = "0123456789abcdef";
	int isneg = (i < 0);
	if (i < 0) {
		i = -i;
	}
	do {
		int digit = i % base;
		buf[--max] = convtbl[digit];
		i -= digit;
		i /= base;
	} while (i && max);
	if (isneg) buf[--max] = '-';
	return buf+max;
}

static char *ultoa(unsigned long i, char *buf, unsigned max, int base)
{
	char convtbl[] = "0123456789abcdef";
	int isneg = (i < 0);
	if (i < 0) {
		i = -i;
	}
	do {
		int digit = i % base;
		buf[--max] = convtbl[digit];
		i -= digit;
		i /= base;
	} while (i && max);
	if (isneg) buf[--max] = '-';
	return buf+max;
}

// Yes this method has a percision loss that even ULONG_MAX doesn't pick up, patches welcome :)
static char *strfromd(long double i, char *buf, int digits, int base)
{
	char convtbl[] = "0123456789abcdef";
	int j = 0, neg = i < 0;
	if (i != i) return "nan";
	if (i == HUGE_VAL) return "inf";
	if (neg) i = fabs(i);
	// 0[...N].[N...]0
	// Probe for N of digits
	long double s = base; int ndig = 0;
	for (;;) {
		ndig++;
		if (i/s < 1) break;
		s *= base;
	}
	if (neg) buf[j++] = '-';

	// Walk Back
	s /= base;
	do {
		double o = i / s;
		buf[j++] = convtbl[(int)(o)%base];
		i -= (double)((int)(i/s))*s;
		s /= base;
	} while (--ndig);


	if (digits) {
		buf[j++] = '.';
		while (digits--) {
			i *= base;
			buf[j++] = convtbl[(int)(i)%base];
		}
	}

	return buf;
}

/* C89 FORMATTING SPECS:
	Number Conversions:

	TAKE %###x
		TAKE %[+-]##x
			TAKE %##[lLh]x
				%d, %i Signed Decimal Int
				%o, %x, %X Unsigned, Octal, hex, HEX
				TAKE %[##].[##]x
					%f [-]ddd.ddd
					%e, %E [-]d.ddd[eE][+-]
					%g, %G
			%s
	%c
	%p
	%%
*/

static struct pfspec {
	enum {CHAR, STRING, PTR,
		USHORT, SHORT, UINT, INT, ULONG, LONG, ULLONG, LLONG,
		FLT, DBL, LDBL, PERCENT} type;
	int initial;
	enum {NONE, SPACE, ZEROS} initialpadding;
	enum {DEF, PLUS,  MINUS} forcedplusormin;
	int decimals;
	int capexp;
} pf;

int vfprintf(FILE *stream, const char *format, va_list va)
{
	enum preformatter {NONE=0, INT, LONG, SHORT} preformatter = NONE;

	for (int i = 0; i < strlen(format); i++) {
		if (!preformatter && format[i] != '%') fputc(format[i], stream);
		else switch(format[++i]) {
			case 'd':
				if (preformatter == LONG)
					 fputs(ltoa(va_arg(va,long), printf_numbuf, 32, 10), stream);
				else fputs(ltoa(va_arg(va, int), printf_numbuf, 32, 10), stream);
				preformatter = 0;
				break;
			case 's':
				fputs(va_arg(va, char *), stream);
				preformatter = 0;
				break;
			case 'p':
				; void *pt = va_arg(va, void *);
				if (!pt) { fputs("(nil)", stream); break; }
				fputs("0x", stream);
				fputs(ultoa((unsigned long)pt,  printf_numbuf, 32, 16), stream);
				preformatter = 0;
				break;
			case 'f':
				fputs(strfromd(va_arg(va, double), printf_numbuf, 6, 10), stream);
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

int fprintf(FILE *stream, const char *format, ...)
{
	va_list va;
	va_start(va, format);
	vfprintf(stream, format, va);
	va_end(va);
	return 0;
}

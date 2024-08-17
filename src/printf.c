#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>

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
	if (i == HUGE_VAL) return   "inf";
	if (i == -HUGE_VAL) return "-inf";
	if (neg) i = fabs(i);
	// 0[...N].[N...]0
	// Probe for N of digits
	long double s = base;
	int ndig = 0;
	for (;;) {
		ndig++;
		if (i/s < 1) break;
		s *= base;
		if (s != s) break;
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

int vfprintf(FILE *stream, char *format, va_list va)
{
	struct pfspec {
		enum {CHAR, STRING, PTR,
			USHORT, SHORT, UINT, INT, ULONG, LONG, ULLONG, LLONG,
			FLT, DBL, LDBL, PERCENT, ERROR} type;
		int initial;
		enum {NONE, SPACE, ZEROS} initialpadding;
		enum {DEF, PLUS,  MINUS} forcedplusormin;
		int decimals;
		int capexp;
	} pf;

	char printf_numbuf[1024];
	for (int i = 0; i < strlen(format); i++) {
		if (format[i] != '%') fputc(format[i], stream);
		else {
			do {
			char *probe = format+i;
			// %c %p %%
			if      (probe[1] == 'c') { pf.type = CHAR; break; }
			else if (probe[1] == 'p') { pf.type = PTR;  break; }
			else if (probe[1] == '%') { pf.type = PTR;  break; }
			// TODO
			else if (probe[1] == 's') { pf.type = STRING;  break; }
			else if (probe[1] == 'f') { pf.type = DBL;  break; }
			else if (probe[1] == 'd') { pf.type = INT;  break; }
			} while (0); // Done so gotos don't have to be used

			format++;


			switch(pf.type) {
			case INT: fputs(ltoa(va_arg(va, int), printf_numbuf, 32, 10), stream); break;
			case STRING: fputs(va_arg(va, char *), stream); break;
			case PTR:
				; void *pt = va_arg(va, void *);
				if (!pt) { fputs("(nil)", stream); break; }
				fputs("0x", stream);
				fputs(ultoa((unsigned long)pt,  printf_numbuf, 32, 16), stream);
				break;
			case DBL: fputs(strfromd(va_arg(va, double), printf_numbuf, 6, 10), stream); break;
			case PERCENT: fputs("%", stream); break;
			case CHAR: fputc((int)(va_arg(va, char)), stream); break;

			case ERROR: // FALLTHROUGH
			default:
				return -1;
			}
		}
	}
	return 1;
}

int printf(char *format, ...)
{
	va_list va;
	va_start(va, format);
	int rv = vfprintf(stdout, format, va);
	va_end(va);
	return rv;
}

int vprintf(char *format, va_list va) { return vfprintf(stdout, format, va); }

int fprintf(FILE *stream, char *format, ...)
{
	va_list va;
	va_start(va, format);
	vfprintf(stream, format, va);
	va_end(va);
	return 0;
}

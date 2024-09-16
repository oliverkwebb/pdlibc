#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <math.h>

struct pfspec {
	enum {CHAR, STRING, PTR, UINT, INT, ULONG, LONG, ULLONG, LLONG, DBL, LDBL, PERCENT, ERROR} type;
	enum {EXTEND = 1, LONGEXT = 2, NORMAL = 0} typemanip;
	int initial;
	enum {NONE, SPACE, ZEROS} initialpadding;
	enum {DEF, PLUS,  MINUS} forcedplusormin;
	int decimals;
	int capexp;
	int expon;
	int base;
};

static char *ltoa(long long i, char *buf, unsigned max, struct pfspec pf)
{
	char *convtbl = pf.capexp ? "0123456789ABCDEF" : "0123456789abcdef";
	int isneg = (i < 0);
	buf[--max] = '\0';
	if (i < 0) {
		i = -i;
	}
	do {
		int digit = i % pf.base;
		buf[--max] = convtbl[digit];
		i -= digit;
		i /= pf.base;
	} while (i && max);
	if (isneg) buf[--max] = '-';
	return buf+max;
}

static char *ultoa(unsigned long long i, char *buf, unsigned max, struct pfspec pf)
{
	char *convtbl = pf.capexp ? "0123456789ABCDEF" : "0123456789abcdef";
	int isneg = (i < 0);
	buf[--max] = '\0';
	if (i < 0) {
		i = -i;
	}
	do {
		int digit = i % pf.base;
		buf[--max] = convtbl[digit];
		i -= digit;
		i /= pf.base;
	} while (i && max);
	if (isneg) buf[--max] = '-';
	return buf+max;
}

// Yes this method has a percision loss that even ULONG_MAX doesn't pick up, patches welcome :)
// Note: THIS CODE IS BUGGY AND ANNOYING IN CONJUNCTION WITH MATH FUNCTIONS, use wisely
static char *strfromd(long double i, char *buf, int digits, struct pfspec pf)
{
	char *convtbl = pf.capexp ? "0123456789ABCDEF" : "0123456789abcdef";
	int j = 0, neg = i < 0;
	if (i != i) return "nan";
	if (i == HUGE_VAL) return   "inf";
	if (i == -HUGE_VAL) return "-inf";
	if (neg) i = fabs(i);
	// 0[...N].[N...]0
	// Probe for N of digits
	long double s = pf.base;
	int ndig = 0;
	for (;;) {
		ndig++;
		if (i/s < 1) break;
		s *= pf.base;
		if (s != s) break;
	}
	if (neg) buf[j++] = '-';


	// Walk Back
	s /= pf.base;
	do {
		double o = i / s;
		buf[j++] = convtbl[(int)(o)%pf.base];
		i -= (double)((int)(i/s))*s;
		s /= pf.base;
	} while (--ndig);


	if (digits) {
		buf[j++] = '.';
		while (digits--) {
			i *= pf.base;
			buf[j++] = convtbl[(int)(i)%pf.base];
		}
	}

	buf[j++] = '\0';

	return buf;
}

static int vfp_fputs_submit(char *str, FILE *stream, char *null)
{
	fputs(str, stream);
	return strlen(str);
}

static int __submit_vfprintf(FILE *stream, char *str, int (*submit)(char *, FILE *, char *), const char *format, va_list va)
{
#define SUBMIT(s) written += submit(s, stream, str)
	struct pfspec pf;
	int written = 0;
	char printf_numbuf[1024];
	for (int i = 0; i < strlen(format); i++) {
		if (format[i] != '%') {
			; char a[2];
			a[1] = '\0';
			a[0] = format[i];
			SUBMIT(a);
		} else {
			int fsiz = 0;
			do {

			pf.typemanip = NORMAL;
			pf.initial = 0;
			pf.initialpadding = DEF;
			pf.forcedplusormin = NONE;
			pf.decimals = 0;
			pf.capexp = 0;
			pf.expon  = 0;
			pf.base = 10;
			fsiz = 1;

			char *probe = format+i;

			// %c %p %% %\0
			if      (probe[1] == 'c') { pf.type = CHAR;     break; }
			else if (probe[1] == 'p') { pf.type = PTR; pf.base = 16; break; }
			else if (probe[1] == '%') { pf.type = PERCENT;  break; }
			else if (!probe[1])       { pf.type = ERROR;    break; }

			if      (probe[1] == '+') { fsiz++; pf.forcedplusormin = PLUS;  }
			else if (probe[1] == '-') { fsiz++; pf.forcedplusormin = MINUS; }

			if (!probe[fsiz]) {
				pf.type = ERROR;
				break;
			} else if (isdigit(probe[fsiz])) {
				char *endptr;
				if (probe[fsiz] == '0') pf.initialpadding = ZEROS;
				pf.initial  = strtol(probe+fsiz, &endptr, 10);
				probe    = endptr;
			}

			if (!probe[fsiz]) {
				pf.type = ERROR;
				break;
			} else if (probe[fsiz] == '.') {
				fsiz++;
				char *endptr;
				pf.decimals = strtol(probe+fsiz, &endptr, 10);
				probe    = endptr;
			}

			if (!probe[fsiz]) {
				pf.type = ERROR;
				break;
			} else if (probe[fsiz] == 'l') { fsiz++; pf.type = LONG; }
			else if (probe[fsiz] == 'L')   { fsiz++; pf.type = EXTEND; }
			else if (probe[fsiz] == 'h')   { fsiz++; }

			if      (probe[fsiz] == 's') { pf.type = STRING;  break; }
			else if (probe[fsiz] == 'f') { pf.type = DBL;  break; }
			else if (probe[fsiz] == 'e') { pf.type = DBL; pf.expon = 1;  break; }
			else if (probe[fsiz] == 'g') { pf.type = DBL; pf.expon = 1;  break; }
			else if (probe[fsiz] == 'E') { pf.type = DBL; pf.expon = 1; pf.capexp = 1;  break; }
			else if (probe[fsiz] == 'G') { pf.type = DBL; pf.expon = 1; pf.capexp = 1;  break; }
			else if (probe[fsiz] == 'd' || probe[fsiz] == 'i') { pf.type = INT;  break; }
			else if (probe[fsiz] == 'u') { pf.type = UINT; break; }
			else if (probe[fsiz] == 'o') { pf.type = INT; pf.base = 8; break; }
			else if (probe[fsiz] == 'x') { pf.type = INT; pf.base = 16; break; }
			else if (probe[fsiz] == 'X') { pf.type = INT; pf.base = 16; pf.capexp = 1; break; }
			else    { pf.type = ERROR; break; }
			} while (0); // Done so gotos don't have to be used

			i += fsiz;

			if (pf.typemanip != NORMAL) {
				if      (pf.type == INT)  pf.type = (int []){INT,  LONG,  LLONG }[pf.typemanip];
				else if (pf.type == UINT) pf.type = (int []){UINT, ULONG, ULLONG}[pf.typemanip];
				else if (pf.type == DBL)  pf.type = (int []){DBL,  LDBL,  LDBL  }[pf.typemanip];
			}
			if (pf.type == STRING && pf.forcedplusormin == MINUS) pf.initialpadding = SPACE;

			switch(pf.type) {
#define NUMPRINT(T, t) case T: SUBMIT(ltoa(va_arg(va, t), printf_numbuf, 32, pf)); break
			NUMPRINT(INT,   int);
			NUMPRINT(LONG,  long);
			NUMPRINT(LLONG, long long);
#undef NUMPRINT
#define NUMPRINT(T, t) case T: SUBMIT(ultoa(va_arg(va, unsigned t), printf_numbuf, 32, pf)); break
			NUMPRINT(UINT,   int);
			NUMPRINT(ULONG,  long);
			NUMPRINT(ULLONG, long long);
#undef NUMPRINT
#define NUMPRINT(T, t) case T: SUBMIT(strfromd(va_arg(va, t), printf_numbuf, 6, pf)); break
			NUMPRINT(DBL,  double);
			NUMPRINT(LDBL, long double);
#undef NUMPRINT

			case CHAR:
				; char a[2];
				a[1] = '\0';
				a[0] = va_arg(va, int);
				SUBMIT(a);
				break;

			case STRING:
				; char *st = va_arg(va, char *) ? : "(nul)";
				size_t len = strlen(st);
				written += SUBMIT(st);
				if (pf.initialpadding == SPACE) for (int i = len; i < pf.initial; i++) SUBMIT(" ");
				break;

			case PTR:
				; void *pt = va_arg(va, void *);
				if (!pt) { written += SUBMIT("(nil)"); break; }
				written += SUBMIT("0x");
				written += SUBMIT(ultoa((unsigned long)pt, printf_numbuf, 32, pf));
				break;

			case PERCENT: written += SUBMIT("%"); break;

			case ERROR: // FALLTHROUGH
			default:
				return -1;
			}
		}
	}
	return written;
}

int vfprintf(FILE *stream, const char *format, va_list va) { return __submit_vfprintf(stream, NULL, vfp_fputs_submit, format, va); }

int printf(const char *format, ...)
{
	va_list va;
	va_start(va, format);
	int rv = vfprintf(stdout, format, va);
	va_end(va);
	return rv;
}

int vprintf(const char *format, va_list va) { return vfprintf(stdout, format, va); }

int fprintf(FILE *stream, const char *format, ...)
{
	va_list va;
	va_start(va, format);
	vfprintf(stream, format, va);
	va_end(va);
	return 0;
}

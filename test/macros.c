#include <stdio.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <stddef.h>
#include <signal.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>

void null(int x, ...) {}

int main(void)
{
	size_t f5; wchar_t f4; ptrdiff_t f3; time_t f2; // "Is the type there"? checks

	printf("%d, %d, %d, %d", EXIT_FAILURE, EXIT_SUCCESS, NULL, EOF);

	if ((unsigned char)(UCHAR_MAX+1)  > (unsigned char)(UCHAR_MAX)  ||
		(unsigned short)(USHRT_MAX+1) > (unsigned short)(USHRT_MAX) ||
		(unsigned int)(UINT_MAX+1)    > (unsigned int)(USHRT_MAX)   ||
		(unsigned long)(ULONG_MAX+1)  > (unsigned long)(ULONG_MAX)  ||
		(short)(SHRT_MAX+1) > (short)(USHRT_MAX) ||
		(int)(INT_MAX+1)    > (int)(INT_MAX)     ||
		(long)(LONG_MAX+1)  > (long)(LONG_MAX)
	) printf("asdsadasdasdads");

	// I DO NOT CARE ABOUT THE VALUE; just be there
	null(0,
// stdio.h
		_IOLBF, _IONBF, _IOFBF, BUFSIZ, FILENAME_MAX, FOPEN_MAX,
		SEEK_SET, SEEK_CUR, SEEK_END,
// errno.h
 		EDOM, ERANGE,
// limits.h
		CHAR_BIT, UCHAR_MAX, SCHAR_MAX, CHAR_MAX, SHRT_MIN, INT_MIN, LONG_MIN, MB_LEN_MAX,
// float.h
		DBL_DIG, DBL_EPSILON, DBL_MANT_DIG, DBL_MAX, DBL_MAX_10_EXP, DBL_MAX_EXP, DBL_MIN,
		DBL_MIN_10_EXP, DBL_MIN_EXP, FLT_DIG, FLT_EPSILON, FLT_MANT_DIG, FLT_MAX, FLT_MAX_10_EXP,
		FLT_MAX_EXP, FLT_MIN, FLT_MIN_10_EXP, FLT_MIN_EXP, FLT_RADIX, FLT_ROUNDS, LDBL_DIG, LDBL_EPSILON,
		LDBL_MANT_DIG, LDBL_MAX, LDBL_MAX_10_EXP, LDBL_MAX_EXP, LDBL_MIN, LDBL_MIN_10_EXP, LDBL_MIN_EXP,
// other
		SIGABRT, SIGFPE, SIGILL, SIGINT, SIGSEGV, SIGTERM, MB_CUR_MAX);
}

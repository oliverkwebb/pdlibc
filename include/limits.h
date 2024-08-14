#ifndef _LIMITS_H
#define _LIMITS_H

#define CHAR_BIT  8
#define MB_LEN_MAX 1

#define UCHAR_MAX 0xFF
#define USHRT_MAX 0xFFFF
#define UINT_MAX  0xFFFFFFFF

#define SCHAR_MAX 0x7F
#define SHRT_MAX  0x7FFF
#define INT_MAX   0x7FFFFFFF

#define SCHAR_MIN 0xFF
#define SHRT_MIN  0xFFFF
#define INT_MIN   0xFFFFFFFF

// DRAGONS (And portability issues) BE HERE
#ifdef __ILP32__
#define LONG_MIN  INT_MIN
#define LONG_MAX  INT_MAX
#define ULONG_MAX UINT_MAX
#else
#define LONG_MIN  0xFFFFFFFFFFFFFFFF
#define ULONG_MAX 0xFFFFFFFFFFFFFFFF
#define LONG_MAX  0x7FFFFFFFFFFFFFFF
#endif
// System Call Wrappers are in X86
#define CHAR_MAX  UCHAR_MAX
#define CHAR_MIN  0

#endif

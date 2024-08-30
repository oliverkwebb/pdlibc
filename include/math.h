#ifndef _MATH_H
#define _MATH_H

// Not in C89, needed for testing and HUGE_VAL
#define INFINITY __builtin_inff()
#define NAN      __builtin_nanf("")

#define HUGE_VAL INFINITY

// These aren't C89 but they are needed _in_ the math functions
#define M_PI   3.14159265358979323846
#define M_E    2.7182818284590452354
#define LOG2_E 1.4426950408889634074
#define M_LN10 2.30258509299404568402

extern double  sqrt(double);
extern double  fabs(double);
extern double frexp(double, int *);
extern double ldexp(double, int);

extern double   sin(double);
extern double   cos(double);
extern double   tan(double);

extern double  asin(double);
extern double  acos(double);
extern double  atan(double);
extern double atan2(double, double);

/*
extern double   log(double);
extern double  log2(double);
extern double log10(double);
extern double   exp(double);
extern double   pow(double, double);

extern double  sinh(double);
extern double  cosh(double);
extern double  tanh(double);

extern double floor(double);
extern double  ceil(double);
*/

#endif

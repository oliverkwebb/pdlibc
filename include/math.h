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

extern double sqrt(double value);
extern double fabs(double value);
extern double  sin(double value);
extern double  cos(double value);
extern double  log(double value);
extern double floor(double value);
extern double ceil(double value);

#endif

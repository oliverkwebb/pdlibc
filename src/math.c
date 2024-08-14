#include <math.h>
// The six transcendental functions everything can be contructed from:
// sin()
// cos()
// sqrt()
// atan()
// log()
// exp() -> pow(e,x) -> 2pow

extern double log2(double);

double sin(double x)  { __asm__ ("fsin"          : "=t"(x) : "0"(x)); return x; }
double sqrt(double x) { __asm__ ("sqrtsd %0, %0" : "=x"(x) : "0"(x)); return x; }
double cos(double x)  { return sin(x + M_PI /2); }
double log(double x)   { return log2(x);}//, 0.30102999566398119521); }

double tan(double x)  { return sin(x)/cos(x); }

/* x86 does NOT have a opcode for fp exponentiation x^y
   However it DOES have one for 2^y

   n^x = 2^(x*log2(n))
   exp(x) = 2^(x*log2(e))

double log2(double x, double y) {
	__asm__ ("fyl2x" : "=&t"(y) : "f"(x), "f"(y));
	return y;
}
double fpow2m1(double x, double y)  { __asm__ ("fxm": "=t"(y) : ""(x)); return x; }
long double pow(long double x, long double y)
{
	return 
}
*/
double fabs(double x)
{
	unsigned long *y = (unsigned long *)(&x);
	*y &= (~0UL) >> 1;
	return x;
}




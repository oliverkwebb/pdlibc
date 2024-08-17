#include <math.h>
// The six transcendental functions everything can be contructed from:
// sin(), cos(), sqrt(), atan(), log(), exp() (-> pow(e,x) -> pow(2, x*ln2(e)))

double sqrt(double x) { __asm__ ("sqrtsd %0, %0" : "=x"(x) : "0"(x)); return x; }

double sin(double x)  { __asm__ ("fsin"          : "=t"(x) : "0"(x)); return x; }
double cos(double x)  { return sin(x + M_PI /2); }
double tan(double x)             { return sin(x)/cos(x); }

double asin(double x) { return ( x==-1 || x==1 ) ? M_PI / 2 * x : atan(x/sqrt(1-x*x)); }
double acos(double x) { return !x ? 0 : M_PI/2-asin(x); }
double atan2(double x, double y) { return atan(x/y);    }

/* x86 does NOT have a opcode for fp exponentiation x^y, However it DOES have one for 2^y
   n^x = 2^(x*log2(n))
*/

extern double __pow2m1(double);

double   pow(double x, double y) { return __pow2m1(y*log2(x))+1; }
double   exp(double x)           { return pow(M_E, x);           }
double log10(double x)           { return log(x)/M_LN10;         }
double ldexp(double x, int exp)  { return x*(1<<exp);            }

double sinh(double x) { return (exp(x)-1/exp(x))/2; }
double cosh(double x) { return (exp(x)+1/exp(x))/2; }
double tanh(double x) { return (exp(x)/(exp(x)+2)); }

double fabs(double x)
{
	unsigned long *y = (unsigned long *)(&x);
	*y &= (~0UL) >> 1;
	return x;
}

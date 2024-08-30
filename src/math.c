#include <math.h>
// The six transcendental functions everything can be contructed from:
// sin(), cos(), sqrt(), atan(), log(), exp() (-> pow(e,x) -> pow(2, x*ln2(e)))

double  sqrt(double x) { __asm__ ("sqrtsd %0, %0" : "=x"(x) : "0"(x)); return x; }
double floor(double x) { __asm__ ("frndint"       : "=t"(x) : "0"(x)); return x; }
double  fabs(double x) { __asm__ ("fabs"          : "=t"(x) : "0"(x)); return x; }
double   sin(double x) { __asm__ ("fsin"          : "=t"(x) : "0"(x)); return x; }
double   cos(double x) { __asm__ ("fcos"          : "=t"(x) : "0"(x)); return x; }

double   tan(double x) { return sin(x)/cos(x); }
double  ceil(double x) { return floor(x)+1; }

// WANTED: ALGORITHMS FOR APPROXIMATING EXP

double frexp(double x, int *exp)
{
	*exp = 0;
	while (x > 2) {
		x /= 2;
		*exp += 1;
	}
	return x;
}

double ldexp(double x, int exp)
{
	while (exp-- > 0) x *= 2;
	return x;
}

// Asm kept blowing up
// Refactored https://stackoverflow.com/questions/23047978/how-is-arctan-implemented
#define  R2 -0x1.58beca04f1805p+6
#define  R3 -0x1.46d547fed8a3dp+0
#define  R4 -0x1.57bd961f06c89p-4
#define  S1  0x1.b189e39236635p+4
#define  S2  0x1.a3b86f7830dc0p+2
#define  S3  0x1.1273f9e5eff20p+1
#define  S4  0x1.44831dafbf542p+0

double atan(double x1) {
  double cons = 0;
  int neg = 0, inv = 0;

  if (x1 < 0) {
  	neg =  1;
  	x1  =- x1;
  }

  if (x1 > 1) {
  	x1  = 1 / x1;
  	inv = 1;
  }

  if (x1 > 0x1.126145e9ecd56p-2) {
  	x1 = (0x1.76cf5d0b09955p-1*x1-1.0+x1)/(x1+0x1.bb67ae8584caap+0);
  	cons = 0x1.0c152382d7365p-1;
  }

  double xsq = x1*x1;
  x1 *= (0x1.9310cfe85307cp+3/(xsq+S1+R2/(xsq+S2+R3/(xsq+S3+R4/(xsq+S4)))));
  x1 += cons;

  if (inv) x1=1.0-x1+0x1.243f6a8885a30p-1;
  if (neg) x1 = -x1;
  return x1;
}

double atan2(double x, double y) { return atan(x/y);    }
double asin(double x) { return ( x==-1 || x==1 ) ? M_PI / 2 * x : atan(x/sqrt(1-x*x)); }
double acos(double x) { return !x ? 0 : M_PI/2-asin(x); }

/*
double   pow(double x, double y) { return __pow2m1(y*log2(x))+1; }
double   exp(double x)           { return pow(M_E, x);           }
double log10(double x)           { return log(x)/M_LN10;         }
double ldexp(double x, int exp)  { return x*(1<<exp);            }

double sinh(double x) { return (exp(x)-1/exp(x))/2; }
double cosh(double x) { return (exp(x)+1/exp(x))/2; }
double tanh(double x) { return (exp(x)/(exp(x)+2)); }
*/

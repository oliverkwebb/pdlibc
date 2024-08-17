#include <math.h>
#include <stdio.h>

double ldexp_wrap(double x, double y) { return ldexp(x,y); }

int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);
	double (*maths[])(double, double) = { atan2, pow, ldexp_wrap, };
	double numbers[] = {45, -100000, -350, -0.0123, 0, 0.123, 350, 100000, NAN};
	for (int i = 0; i < sizeof(maths)/sizeof(maths[0]); i++)
		for (int j = 0; j < sizeof(numbers)/sizeof(numbers[0]); j++)
			for (int k = 0; k < sizeof(numbers)/sizeof(numbers[0]); k++)
				printf("%d[%d %d]: %f\n", i, j, k, (maths[i])(numbers[j], numbers[k]));
}

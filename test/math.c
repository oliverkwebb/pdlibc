#include <math.h>
#include <stdio.h>

int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);
	double (*maths[])(double) = {
		fabs,
		sin,
		cos,
		tan,
		atan,
		asin,
		acos,
//		log10,
		sqrt,
//		exp,
//		sinh,
//		cosh,
//		tanh,
//		log,
		};
	double numbers[] = {45, -100000, -350, -0.0123, 0, 0.123, 350, 100000, NAN};
	for (int i = 0; i < sizeof(maths)/sizeof(maths[0]); i++)
		for (int j = 0; j < sizeof(numbers)/sizeof(numbers[0]); j++)
			printf("%d, %d: %f\n", i, j, (maths[i])(numbers[j]));
}

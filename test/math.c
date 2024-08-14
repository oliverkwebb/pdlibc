#include <math.h>
#include <stdio.h>

int main()
{
	double (*maths[])(double) = {sqrt, fabs, sin, cos};//, log, floor, ceil};
	double numbers[] = {-100000, -350, -0.0123, 0, 0.123, 350, 100000, NAN};
	for (int i = 0; i < sizeof(maths)/sizeof(maths[0]); i++)
		for (int j = 0; j < sizeof(numbers)/sizeof(numbers[0]); j++)
			printf("%d, %d: %f\n", i, j, (maths[i])(numbers[j]));
}

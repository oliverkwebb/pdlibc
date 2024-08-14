#include <stdio.h>
#include <float.h>
#include <limits.h>

int main (int argc, char **argv)
{
	printf("%f, %f, %f, %f, %f, %f\n",
	        2.5, 0.01234, (double)250, -120.0, 999999999999999.0, (double)ULONG_MAX);
}

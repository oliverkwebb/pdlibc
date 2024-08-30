#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, char **argv)
{
	// Basic use of %d and %s
	printf("Hello World, %d, %i, %s, %d\n", 34, -21, "UwU", INT_MAX);
	// Floating Point
	printf("%f, %f, %f, %f, %f, %f\n", 2.5, 0.01234, (double)250, -120.0, 999999999999999.0, (double)ULONG_MAX);
	// Pointers
	printf("%p, %p, %p\n", (void *)1, (void *)ULONG_MAX, (void *)0xdeadbeef, 0);
	// Basic %u, %x, %c, %%
	printf("%u %x %X %c %c %c %%\n", -12, 32, 14, 'a', 'b', ' ');
}

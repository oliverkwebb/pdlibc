#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, char **argv)
{
	switch (argc) {
		case 1: // Basic use of %d and %s
			printf("Hello World, %d, %d, %s, %d\n", 34, -21, "UwU", INT_MAX);
			break;
		case 2:	// Floating Point
			printf("%f, %f, %f, %f, %f, %f\n", 2.5, 0.01234, (double)250,
			-120.0, 999999999999999.0, (double)ULONG_MAX);
			break;
		case 3: // Pointers
			printf("%p, %p, %p\n", (void *)1, (void *)ULONG_MAX, (void *)0xdeadbeef, 0);
			break;
	}
}

#include <stdio.h>
#include <stdlib.h>

int main()
{
	// Multiple split-pages
	char *x = malloc(10);
	free(x);
	for (int i = 0; i < 2000; i++) {
	x = malloc(10);
	x[9] = 'a';
	x[8] = 'a';
	x[7] = 'a';
	x[6] = 'a';
	}
	puts(x+6);
	free(x);
}

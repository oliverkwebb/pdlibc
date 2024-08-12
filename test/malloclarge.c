#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *x = malloc(10000);
	char *y = malloc(10000);
	free(x);
	char *z = malloc(10000);
	free(y);
	free(z);
}

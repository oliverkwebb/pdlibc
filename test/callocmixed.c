#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *x = calloc(64, 1);
	char *y = calloc(200, 1);
	char *z = calloc(200, 1);
	char *a = calloc(64, 1);
	free(y);
	char *b = calloc(64, 1);
	free(z);
	free(b);
	free(a);
	char *c = calloc(64, 1);
	free(x);
	free(c);
}

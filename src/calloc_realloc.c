#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void *calloc(size_t nmemb, size_t size)
{
	void *p = malloc(nmemb * size);
	memset(p, 0, nmemb * size);
	return p;
}

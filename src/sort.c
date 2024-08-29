// Standard doesn't say I _have_ to do quicksort :P
#include <string.h>

void qsort(void *base, size_t nmemb, size_t size, int (*comp)(const void *, const void *))
{
	size_t j = nmemb-1;
	char buf[size];
	for (int i = 0; i < j; i++) {
		for (int k = 0; k < nmemb-1; k++) {
			if (comp(base+(k*size), base+((k+1)*size)) > 0) {
				memcpy(buf, base+(k*size), size);
				memcpy(base+(k*size), base+((k+1)*size), size);
				memcpy(base+((k+1)*size), buf, size);
			}
		}
		nmemb--;
	}
}

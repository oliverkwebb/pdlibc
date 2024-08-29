// Standard doesn't say I _have_ to do quicksort :P
#include <string.h>

void qsort(void *base, size_t nmemb, size_t size, int (*comp)(const void *, const void *))
{
	size_t j = nmemb-1;
	char buf[size];
	for (size_t i = 0; i < j; i++) {
		for (size_t k = 0; k < nmemb-1; k++) {
			if (comp(base+(k*size), base+((k+1)*size)) > 0) {
				memcpy(buf, base+(k*size), size);
				memcpy(base+(k*size), base+((k+1)*size), size);
				memcpy(base+((k+1)*size), buf, size);
			}
		}
		nmemb--;
	}
}

// I'll actually do a O(n log n) algorithm here
void *bsearch(const void *key, const void *base, size_t nmemb, size_t size, int (*comp)(const void *, const void *))
{
	size_t L = 0;
	size_t R = nmemb - 1;
	while (L <= R) {
		size_t cele = (L + R) / 2;
		int cmp = comp(key, base+(cele*size));
		if (!cmp) return  base+(cele*size);
		else if (cmp > 0) L = cele + 1;
		else              R = cele - 1;
	}
	return NULL;
}

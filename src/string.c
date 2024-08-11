#include <stddef.h>

size_t strlen(char *p)
{
	int a;
	for(a = 0; p[a]; a++);
	return a;
}

void *memset(void *str, int c, size_t n)
{
	char *s = str;
	int a = 0;
	while (a < n) {
		*s = c;
		s++, a++;
	}
	return s;
}

void *memcpy(void *dest, void *from, size_t n)
{
	char *d = dest;
	char *f = from;
	while (n--) {
		*d = *f;
		d++, f++;
	}
	return d;
}

int strcmp(char *s1, char *s2)
{
	for(; *s1 == *s2 && *s1; s1++, s2++);
	return (int)(*s1) - (int)(*s2);
}

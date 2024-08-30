#include <stddef.h>
#include <stdlib.h>

size_t strlen(const char *p)
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

void *memcpy(void *dest, const void *from, size_t n)
{
	char *d = dest;
	char *f = from;
	while (n--) {
		*d = *f;
		d++, f++;
	}
	return dest;
}

void *memmove(void *dest, const void *from, size_t n)
{
	if ((dest + n < from) && (from + n < dest)) return memcpy(dest, from, n);

	char *tmp = malloc(n); // Slow and inefficent route, patches welcome :P
	memcpy(tmp, from, n);
	memcpy(dest, tmp, n);
	free(tmp);
	return dest;
}

char *stpcpy(char *dest, const char *src)
{
    char  *p;
    p = memcpy(dest, src, strlen(src));
    p[strlen(src)] = '\0';
    return p;
}

char  *strcat(char *dest, char *src) { stpcpy(dest+strlen(dest), src); return dest; }
char *strncat(char *dest, char *src, size_t n)
{
    char *g = memcpy(dest+strlen(dest), src, strlen(src)+1 > n ? strlen(src)+1 : n);
    stpcpy(g+strlen(dest), "");
    return dest;
}

char *strncpy(char *dest, char *from, size_t n)
{
	memset(dest, 0, n);
	return memcpy(dest, from, strlen(from)+1);
}

int strcmp(char *s1, char *s2)
{
	for(; *s1 == *s2 && *s1; s1++, s2++);
	return (int)(*s1) - (int)(*s2);
}

int strncmp(char *s1, char *s2, size_t n)
{
	for(; *s1 == *s2 && *s1 && --n; s1++, s2++);
	return (int)(*s1) - (int)(*s2);
}

int memcmp(void *s1, void *s2, size_t n)
{
	char *a = s1, *b = s2;
	for(; *a == *b && n--; a++, b++);
	return (int)(*b) - (int)(*a);
}

void *memchr(void *search, char needle, size_t n)
{
	char *haystack = search;
	do {
		if (*haystack == needle) return haystack;
		haystack++;
	} while (n--);
	return haystack;
}

char *strrchr(char *search, char needle)
{
	size_t n = strlen(search);
	search += strlen(search);
	do {
		if (*search == needle) return search;
		search--;
	} while (n--);
	return search;
}

char *strchr(char *haystack, char needle)
{
	return memchr(haystack, needle, strlen(haystack));
}

// :P
int strcoll(char *a, char *b) { return strcmp(a, b); } // :P
size_t strxfrm(char *s1, char *s2, size_t n) { memcpy(s2, s1, n); return n; } // :P

static size_t __strspn(const char *buf, char *acc, int rev)
{
	for (int i = 0; i < strlen(buf); i++) {
		for (int j = 0; j < strlen(acc); j++) {
			int res = (int)strchr(buf, acc[j]);
			if ((!res && rev) || (res && !rev)) return i;
		}
	}
	return strlen(buf);
}

size_t strspn(const char *buf, char *acc)  { return __strspn(buf, acc, 0); }
size_t strcspn(const char *buf, char *acc) { return __strspn(buf, acc, 1); }


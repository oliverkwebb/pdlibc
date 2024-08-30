# pdlibc - A Demonstration libc that's C89 compatible
---

pdlibc (Public Domain Libc) is a example implementation of the standard C library designed to be as simple as posible.

It currently provides most of the subset of functions from C89 and the linux kernels [nolibc](https://github.com/torvalds/linux/tree/master/tools/include/nolibc)

The functions that have had full tests for them (`make test`):

- abort()
- assert()
- atexit(), exit()
- atoi(), atol(), strtod()
- bsearch()
- calloc()
- cos()
- fabs()
- fopen()
- free()
- fwrite()
- getenv()
- atan() and atan2()
- setlocale(), localeconv()
- rand(), srand()
- IO buffering (setvbuf, fflush)
- labs(), abs()
- malloc()
- memcpy()
- memmove()
- memset()
- putchar()
- puts()
- qsort()
- raise()
- sin()
- Most of printf(), vfprintf(), vprintf(), and fprintf();
- sqrt()
- strcat()
- strchr(), memchr()
- strcmp(), strncmp()
- strcpy(), strncpy(), memcpy()
- strerror()
- strlen()
- The entirity of ctype.h
- The entirity of varargs.h

See:
https://port70.net/%7Ensz/c/c89/c89-draft.html#4.

# pdlibc - A Demonstration libc that's C89 compatible
---

pdlibc (Public Domain Libc) is a example implementation of the standard C library designed to be as simple as posible.

It currently provides most of the subset of functions from C89 and the linux kernels [nolibc](https://github.com/torvalds/linux/tree/master/tools/include/nolibc)

The functions that have had full tests for them (`make test`):

- assert()
- The entirity of ctype.h
- cos()
- sin()
- sqrt()
- fabs()
- raise()
- abort()
- The entirity of varargs.h
- fopen()
- fwrite()
- putchar()
- puts()
- Some of printf() (Which currently supports %s, %d, %c, %%, %p, %u, %o, and %x)
- IO buffering (setvbuf, fflush)
- malloc()
- calloc()
- free()
- atoi(), atol(), strtod()
- atexit(), exit()
- getenv()
- labs(), abs()
- memcpy()
- memmove()
- strcpy(), strncpy(), memcpy()
- strcat()
- strchr(), memchr()
- strlen()
- memset()
- strcmp(), strncmp()
- strerror()

See:
https://port70.net/%7Ensz/c/c89/c89-draft.html#4.

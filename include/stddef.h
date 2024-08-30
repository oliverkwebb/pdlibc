#ifndef _STDDEF_H
#define _STDDEF_H

typedef signed long size_t;
typedef unsigned long long ptrdiff_t;
typedef unsigned int wchar_t;

#define NULL (void *)0
#define offsetof(type, member) __builtin_offsetof(type, member)

#endif

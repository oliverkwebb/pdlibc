// Exclusive Interal Syscalls
#ifndef ___SYSCALLS_H
#define ___SYSCALLS_H
#include <stddef.h>
extern size_t read(int, void *, int);
extern size_t write(int, void *, int);
extern void _Exit(int);
extern int kill(int, int);
extern int getpid(void);
extern void *mmap(void *, size_t, int, int, int, long);
extern int munmap(void *, size_t);
#endif

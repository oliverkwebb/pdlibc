#ifndef _SIGNAL_H
#define _SIGNAL_H

typedef int sig_atomic_t;
typedef void (*sighandler_t)(int);
typedef struct __sigset_t { unsigned long _[32]; } sigset_t;

#define SIGABRT 6
#define SIGFPE 8
#define SIGILL 9
#define SIGINT 2
#define SIGSEGV 11
#define SIGTERM 15

#define SIG_DFL 0
#define SIG_IGN 1
#define SIG_ERR -1

extern int raise(int);

#endif

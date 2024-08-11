#ifndef _SIGNAL_H
#define _SIGNAL_H

#define SIGABRT 6
#define SIGFPE 8
#define SIGILL 9
#define SIGINT 2
#define SIGSEGV 11
#define SIGTERM 15

extern int raise(int);

#endif

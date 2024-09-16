#include <signal.h>

// TODO: Handle the linux signal subsystem
/* Notes:
// It's nice that the signal documentation is for libc and NOT the kernel \s
0xC0000000
 18 #define SA_SIGINFO    4
 17 #define SA_ONSTACK    0x08000000
 16 #define SA_RESTART    0x10000000
 15 #define SA_NODEFER    0x40000000
 14 #define SA_RESETHAND  0x80000000
 13 #define SA_RESTORER   0x04000000
 10 #define SIG_ERR  ((void (*)(int))-1)
  9 #define SIG_DFL  ((void (*)(int)) 0)
  8 #define SIG_IGN  ((void (*)(int)) 1)
*/

typedef struct siginfo_t siginfo_t;
extern int      kill(int, int);
extern int    getpid(void);

int raise(int sig)
{
	return kill(getpid(), sig);
}

void abort(void)
{
	raise(SIGABRT);
}


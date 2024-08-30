#include <signal.h>

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


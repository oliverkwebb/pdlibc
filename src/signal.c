#include <signal.h>
#include <__syscalls.h>

extern int   kill(int, int);
extern int getpid(void);

int raise(int sig)
{
	return kill(getpid(), sig);
}

void abort(void)
{
	raise(SIGABRT);
}

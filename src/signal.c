#include <signal.h>
#include <__syscalls.h>

int raise(int sig)
{
	return kill(getpid(), sig);
}

void abort(void)
{
	raise(SIGABRT);
}

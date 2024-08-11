#include <signal.h>
#include <__syscalls.h>

int raise(int sig)
{
	return kill(getpid(), sig);
}

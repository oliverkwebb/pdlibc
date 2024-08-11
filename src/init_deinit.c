#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <__syscalls.h>

void (*run_atexit)(void) = NULL;

int atexit(void (*func)(void)) // TODO: Multiple Functions
{
	run_atexit = func;
	return 0;
}

extern void ioflush(void); // TEMP

extern int main(int argc, char **argv, char **envp);

static char stdinbuf[BUFSIZ], stdoutbuf[BUFSIZ], stderrbuf[BUFSIZ];

void ___runc(int argc, char **argv)
{
	stdin->buffer = stdinbuf;
	stdout->buffer = stdoutbuf;
	stderr->buffer = stderrbuf;
	stdin->fd  = 0;
	stdout->fd = 1;
	stderr->fd = 2;

	exit(main(argc, argv, argv+(argc+1)));
}

void exit(int value)
{
	if (run_atexit) run_atexit();
	fflush(NULL);
	_Exit(value);
}

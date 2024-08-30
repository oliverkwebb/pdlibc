#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>

extern void _Exit(int);
extern int execve(const char *, char **, char **);

static void (*run_atexit[32])(void);
static int atexit_regidx = 0;

int atexit(void (*func)(void))
{
	if (atexit_regidx > 31) return 1;
	run_atexit[atexit_regidx++] = func;
	return 0;
}

extern int main(int argc, char **argv, char **envp);

// Environ Handling also happens here, including system()
static char **environ;
char *getenv(char *name) {
	char **env = environ;
	while (*env) {
		if (!strncmp(*env, name, strlen(name)))
			return *env + strlen(name) + 1;
		env++;
	}
	return NULL; // NULL
}

int system(const char *cmd)
{
	char *args[] = {"-c", (char *)cmd, NULL};
	return execve("/bin/sh", args, environ);
}

void ___runc(int argc, char **argv)
{
	stdin->buffer  = malloc(BUFSIZ);
	stdout->buffer = malloc(BUFSIZ);
	stderr->buffer = malloc(BUFSIZ);
	stdin->bufsize  = BUFSIZ;
	stdout->bufsize = BUFSIZ;
	stderr->bufsize = BUFSIZ;
	stdin->bufmode  = _IOLBF;
	stdout->bufmode = _IOLBF;
	stderr->bufmode = _IOLBF;
	stdin->fd  = 0;
	stdout->fd = 1;
	stderr->fd = 2;
	environ = argv+(argc+1);

	volatile char a[250];

	exit(main(argc, argv, argv+(argc+1)));
}

void exit(int value)
{
	for (int i = 0; i < atexit_regidx; i++) run_atexit[i]();
	fflush(NULL);
	_Exit(value);
}

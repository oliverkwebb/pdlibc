#include <stdio.h>
#include <stddef.h>

void (*run_atexit)(void) = NULL;

int atexit(void (*func)(void))
{
	run_atexit = func;
	return 0;
}

void ___init_libc(void)
{
}

extern void ioflush(void); // TEMP

int ___end_libc(int value)
{
	if (run_atexit) run_atexit();
	ioflush();
	return value;
}

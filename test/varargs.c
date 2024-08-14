#include <stdarg.h>

volatile void vfgive(int a, va_list va)
{
}

volatile void null(int a, ...)
{
	va_list va;
	va_start(va, a);
	vfgive(a, va);
	va_end(va);
}

int main()
{
	null(1, 2, "3", '4', (float)5.0, (int *)6, (double)7, (short)8, 50L, 1U, 1ULL);
}

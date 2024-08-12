#include <ctype.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	int (*ctypes[])(int) = {
		isalnum, isalpha, iscntrl, isdigit, isgraph,
		islower, isprint, ispunct, isspace, isupper,
		isxdigit
	};

	int (*cf)(int) = NULL;

	for (int i = 0; i < 11; i++) {
		cf = ctypes[i];
		// There are 2 different behavoirs, musls one is simpler, ignoring post-0xFF characters
		for (int j = 0; j < 256; j++) putchar(cf(j) ? 'y' : 'n');
		printf("::: %d\n", i);
	}
}

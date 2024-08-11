#include <stdio.h>

int main(int argc, char **argv) {
	if (!argv[1]) return 1;
	puts(argv[1]);
	return 0;
}

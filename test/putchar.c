#include <stdio.h>
#include <string.h>
// Also a test of buffering since the default is _IOLBF
int main(int argc, char *argv[]) {
	if (argc != 2) return 42;
	for (int i = 0; i < strlen(argv[1]); i++) putchar(argv[1][i]);
}

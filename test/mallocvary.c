#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	void *mal[16];
	int mp = 0;
	for (int i = 1; i < argc; i++) {
		if (argv[i][0] == 'f') free(mal[mp--]);
		else {
			mal[++mp] = malloc(atol(argv[i]));
			memset(mal[mp], 0, atol(argv[i]));
		}
	}
	printf("%d\n", mp);
}

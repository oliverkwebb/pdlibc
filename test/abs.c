#include <stdio.h>
#include <stdlib.h>

char buf[40];

#ifndef STRFROMI
char *strfromi(int i, char *buf, int u1, int u2)
{
	char *bf;
	asprintf(&bf, "%d", i);
	return bf;
}
#endif


int main(int argc, char **argv)
{
	int numbers[] = {0, 1, 350, -1, -350};
	long lumbers[] = {0, 1, 350, -1, -350};
	for (int i = 0; i < 5; i++)
		puts(strfromi(abs(numbers[i]), buf, 40, 10));
	for (int i = 0; i < 5; i++)
		puts(strfromi(labs(lumbers[i]), buf, 40, 10));
}

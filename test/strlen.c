#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char buf[40];

#ifndef STRFROMI
char *strfromi(int i, char *buf, int, int)
{
	char *bf;
	asprintf(&bf, "%d", i);
	return bf;
}
#endif

int main(int argc, char **argv)
{
	puts(strfromi(strlen(argv[1]), buf, 40, 10));
}

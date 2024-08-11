#include <stdio.h>
#include <stdlib.h>

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
	puts(strfromi(argc, buf, 40, 10));
}

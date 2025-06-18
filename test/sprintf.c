#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

int main(int argc, char **argv)
{
	char strbuf[300];
	memset(strbuf, 0, 200);
	sprintf(strbuf, "%d, %i, %s", 34, -21, "UwU");
	puts(strbuf);
	putchar(strbuf[0]);
	putchar(strbuf[1]);
	putchar(strbuf[3]);
	putchar(strbuf[4]);
}

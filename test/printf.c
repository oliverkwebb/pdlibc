#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	printf("Hello World, %d, %d, %s\n", 34, -21, argv[1] ? argv[1] : "sdasdasdsad" );
	return 0;
}

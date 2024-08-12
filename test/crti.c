#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	volatile int array[] = {0,1,2,3,4,5,6,7,8,9,0};
	printf("%d\n", argc);
	return array[10];
}

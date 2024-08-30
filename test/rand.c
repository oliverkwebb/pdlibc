#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	for (int i = 0; i < 100; i++) printf("%d\n", rand());
	srand(500);
	for (int i = 0; i < 100; i++) printf("%d\n", rand());
}
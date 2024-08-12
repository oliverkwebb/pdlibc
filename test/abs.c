#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int numbers[] = {0, 1, 350, -1, -350};
	long lumbers[] = {0, 1, 350, -1, -350};
	for (int i = 0; i < 5; i++)
		printf("%d\n", abs(numbers[i]));
	for (int i = 0; i < 5; i++)
		printf("%d\n", (int)labs(lumbers[i]));
}

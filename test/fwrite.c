#include <stdio.h>

int main(int argc, char **argv)
{
	int n[] = {2,3,4,5,6};
	fwrite(&n, sizeof(int), 5, stdout);
}

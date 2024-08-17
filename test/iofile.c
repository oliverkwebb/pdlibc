#include <stdio.h>

int main()
{
	FILE *a = fopen("test/files/iofile-examp", "w+");
	fputs("42", a);
	fclose(a);
}

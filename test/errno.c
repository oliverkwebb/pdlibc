#include <errno.h>
#include <stdio.h>

int main()
{
	errno = EDOM;
	perror(NULL);
	errno = ERANGE;
	perror("Meow");
	errno = -75;
	perror("");
}

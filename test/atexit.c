#include <stdio.h>
#include <stdlib.h>

void ratexit(void) {puts("UwUUwUUwU");}

int main(void) {
	atexit(ratexit);
	atexit(ratexit);
	atexit(ratexit);
	return 0;
}

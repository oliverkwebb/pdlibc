#include <stdio.h>
#include <stdlib.h>

void ratexit(void) {puts("UwUUwUUwU");}

int main(void) {
	atexit(ratexit);
	return 0;
}

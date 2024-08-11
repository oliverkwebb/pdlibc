#include <stdio.h>
#include <stdlib.h>

void ratexit() {puts("UwUUwUUwU");}

int main() {
	atexit(ratexit);
	return 0;
}

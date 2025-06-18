#include <stdio.h>
#include <string.h>
#include <time.h>

int main() {
	struct tm tm;
	memset(&tm, 0, sizeof(struct tm));
	puts(asctime(&tm));
}

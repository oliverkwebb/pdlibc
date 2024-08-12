#include <errno.h>
#include <stdio.h>
#include <stddef.h>
#include <limits.h>

int abs(int n) { return n > 0 ? n : -n; }
long labs(long n) { return n > 0 ? n : -n; }

#include <locale.h>

// :P
char *setlocale(int c, char *l) {return ":P";}
struct lconv lp;
struct lconv *localeconv(void) {return &lp;}

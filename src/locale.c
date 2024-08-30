#include <locale.h>
#include <limits.h>

char *setlocale(int c, char *l) {return "C";} // :P
struct lconv lp = {".", "", "", "", "", "", "", "", "", CHAR_MAX, CHAR_MAX, CHAR_MAX, CHAR_MAX, CHAR_MAX, CHAR_MAX, CHAR_MAX, CHAR_MAX};
struct lconv *localeconv(void) {return &lp;}

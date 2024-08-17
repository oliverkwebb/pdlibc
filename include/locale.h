#ifndef _LOCALE_H
#define _LOCALE_H

#include <stddef.h>

struct lconv {
#define S(x) char *x
#define C(x) char x
	S(decimal_point);
	S(thousands_sep);
	S(grouping);
	S(int_curr_symbol);
	S(mon_decimal_point);
	S(mon_thousands_sep);
	S(mon_grouping);
	S(positive_sign);
	S(negative_sign);
	C(int_frac_digits);
	C(frac_digits);
	C(p_cs_precedes);
	C(p_sep_by_space);
	C(n_cd_precedes);
	C(n_sep_by_space);
	C(p_sign_posn);
	C(n_sign_posn);
#undef  S
#undef  C
};

#define LC_ALL      NULL
#define LC_COLLATE  NULL
#define LC_CTYPE    NULL
#define LC_MONETARY NULL
#define LC_NUMERIC  NULL
#define LC_TIME     NULL

char *setlocale(int, char *);
struct lconv *localeconv(void);

#endif

#ifndef _TIME_H
#define _TIME_H

#include <stddef.h>

typedef long long time_t;
typedef long long clock_t;

struct tm {
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
	int tm_yday;
	int tm_isdst;
};

#define CLK_TICK 1000000 // Removed from later C versions

extern time_t time(time_t *);
extern time_t mktime(struct tm *);
extern time_t difftime(time_t, time_t);


#endif

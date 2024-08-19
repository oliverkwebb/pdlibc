#include <time.h>
extern time_t time(time_t *);

#define isleap(y) ((!(y % 4)) ? ((!(y % 100)) ? !(y % 400) : 1) : 0)

static int  daylens[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static char *mnames[] = {"January", "Febuary", "March", "April", "May", "June", "July", "August",
						"September", "October", "November", "December"};
static char   *days[] = {"Monday", "Tuesday", "Wednesday", "Thrusday", "Friday", "Saturday", "Sunday"};

static int tmcheck(struct tm t)
{
	if ((unsigned) t.tm_sec > 60 ||
		(unsigned) t.tm_min > 60 ||
		(unsigned) t.tm_hour> 24 ||
		(unsigned) t.tm_mon > 12 ||
		(t.tm_mday && (unsigned)(t.tm_mday) > daylens[t.tm_mon] )||
		(unsigned) t.tm_wday > 6) return 1;
	else return 0;
}

time_t difftime(time_t t1, time_t t2) {return t1 - t2;}

time_t mktime(struct tm *tptr)
{
	time_t time = 0;
	if (tmcheck(*tptr)) return -1;
	time += tptr->tm_sec;
	time += tptr->tm_min  * (60);
	time += tptr->tm_hour * (60*60);
	time += tptr->tm_mday * (60*60*24);
	time += tptr->tm_mon  * (60*60*24*daylens[tptr->tm_mday]);
	time += (70+tptr->tm_year) * (60*60*24*daylens[tptr->tm_mday]*(isleap(tptr->tm_year)));
	return time;
}

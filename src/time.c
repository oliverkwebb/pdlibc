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

clock_t clock() {
	struct timespec {
		time_t tvs;
		time_t tvns;
	} ts;
	extern int clock_gettime(int, struct timespec *);
	clock_gettime(2/*CLOCK_PROCESS_CPUTIME_ID*/, &ts);
	return ts.tvs*CLK_TICK + ts.tvns*(CLK_TICK/1000);
}

// Timezone handling is messy and C89 says "uhdunno deal with it" in response
//
// https://gitlab.com/libtime/documentation/-/wikis/Timezones
// Not writing a TZif parser or a POSIX time zone string parser
// Everything is UTC always!

// Note: These 4 functions have _r versions that don't access global variables.
// I am including these 4 in the library even if they aren't standard C89.
// It's the right thing (TM).

char asctime_global_buf[26];
char ctime_global_buf[26];
struct tm gmtime_global_buf;
struct tm localtime_global_buf;

#ifndef TIME_H
#define TIME_H

#include <stddef.h>

// Time constants
#define CLOCKS_PER_SEC 1000000 // idk wtf this is

// Type definitions
typedef long time_t;       // Represents seconds since the epoch
typedef long clock_t;      // Represents processor time

// Struct for broken-down time
struct tm {
    int tm_sec;    // Seconds [0, 59]
    int tm_min;    // Minutes [0, 59]
    int tm_hour;   // Hours [0, 23]
    int tm_mday;   // Day of the month [1, 31]
    int tm_mon;    // Month since January [0, 11]
    int tm_year;   // Years since 1900
    int tm_wday;   // Day of the week [0, 6] (Sunday = 0)
    int tm_yday;   // Day of the year [0, 365]
    int tm_isdst;  // Daylight Saving Time flag
};

// Function declarations

// Get the current calendar time
time_t time(time_t *t);

// Convert calendar time to broken-down time (UTC)
struct tm *gmtime(const time_t *timer);

// Convert calendar time to broken-down time (local time)
struct tm *localtime(const time_t *timer);

// Format a broken-down time into a string
char *asctime(const struct tm *timeptr);

// Format calendar time as a string
char *ctime(const time_t *timer);

// Convert broken-down time to calendar time
time_t mktime(struct tm *timeptr);

// Get the processor time used
clock_t clock(void);

// Format time as a string (reentrant)
size_t strftime(char *s, size_t max, const char *format, const struct tm *timeptr);

#endif // TIME_H

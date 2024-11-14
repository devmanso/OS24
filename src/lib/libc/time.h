#ifndef TIME_H
#define TIME_H

#include <stdint.h>

typedef long time_t;

// Structure to hold calendar time information
struct tm {
    int tm_sec;   // Seconds after the minute [0-60]
    int tm_min;   // Minutes after the hour [0-59]
    int tm_hour;  // Hours since midnight [0-23]
    int tm_mday;  // Day of the month [1-31]
    int tm_mon;   // Months since January [0-11]
    int tm_year;  // Years since 1900
    int tm_wday;  // Days since Sunday [0-6]
    int tm_yday;  // Days since January 1 [0-365]
    int tm_isdst; // Daylight Saving Time flag
};

// Function prototypes
time_t time(time_t *tloc);
struct tm *localtime(const time_t *timer);
struct tm *gmtime(const time_t *timer);
time_t mktime(struct tm *timeptr);

#endif // TIME_H

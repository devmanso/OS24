#include "time.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "../../kernel/drivers/ports.h"

// Constants for the epoch
#define EPOCH_YEAR 1970
#define SECONDS_PER_MINUTE 60
#define SECONDS_PER_HOUR 3600
#define SECONDS_PER_DAY 86400
#define DAYS_IN_YEAR 365
#define DAYS_IN_LEAP_YEAR 366
#define CMOS_ADDRESS 0x70
#define CMOS_DATA 0x71

#define CLOCKS_PER_SEC 1000000 // for clock() implementation

// Leap year helper functions
int is_leap_year(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

int days_in_year(int year) {
    return is_leap_year(year) ? DAYS_IN_LEAP_YEAR : DAYS_IN_YEAR;
}

// Days in each month
static const int days_per_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

unsigned int read_rtc_register(unsigned int reg) {
    outb(reg, CMOS_ADDRESS);
    return inb(CMOS_DATA);
}

unsigned int bcd_to_decimal(unsigned int bcd) {
    return (bcd & 0x0F) + ((bcd >> 4) * 10);
}

// Helper to fill a tm struct
void fill_tm_struct(struct tm *timeptr, unsigned int hour, unsigned int minute, unsigned int second, unsigned int day, unsigned int month, unsigned int year, unsigned int weekday) {
    timeptr->tm_sec = second;
    timeptr->tm_min = minute;
    timeptr->tm_hour = hour;
    timeptr->tm_mday = day;
    timeptr->tm_mon = month - 1;  // tm_mon is 0-indexed
    timeptr->tm_year = year + 100;  // tm_year is years since 1900
    timeptr->tm_wday = weekday - 1; // tm_wday is 0-indexed, Sunday = 0
    timeptr->tm_yday = 0;           // Calculate later if needed
    timeptr->tm_isdst = -1;         // Not handling DST here
}

time_t time(time_t *t) {
    unsigned int second, minute, hour, day, month, year, weekday;
    second = bcd_to_decimal(read_rtc_register(0x00));
    minute = bcd_to_decimal(read_rtc_register(0x02));
    hour = bcd_to_decimal(read_rtc_register(0x04));
    day = bcd_to_decimal(read_rtc_register(0x07));
    month = bcd_to_decimal(read_rtc_register(0x08));
    year = bcd_to_decimal(read_rtc_register(0x09)) + 2000;

    // Convert to epoch time
    time_t seconds_since_epoch = 0;
    for (int y = EPOCH_YEAR; y < year; y++) {
        seconds_since_epoch += days_in_year(y) * SECONDS_PER_DAY;
    }

    for (int m = 0; m < month - 1; m++) {
        seconds_since_epoch += days_per_month[m] * SECONDS_PER_DAY;
        if (m == 1 && is_leap_year(year)) {
            seconds_since_epoch += SECONDS_PER_DAY; // February in leap year
        }
    }

    seconds_since_epoch += (day - 1) * SECONDS_PER_DAY;
    seconds_since_epoch += hour * SECONDS_PER_HOUR;
    seconds_since_epoch += minute * SECONDS_PER_MINUTE;
    seconds_since_epoch += second;

    if (t) {
        *t = seconds_since_epoch;
    }
    return seconds_since_epoch;
}

struct tm *gmtime(const time_t *timer) {
    static struct tm timeinfo;
    time_t t = *timer;

    // Break down time
    int year = EPOCH_YEAR;
    while (t >= days_in_year(year) * SECONDS_PER_DAY) {
        t -= days_in_year(year) * SECONDS_PER_DAY;
        year++;
    }

    timeinfo.tm_year = year - 1900;

    int month = 0;
    while (t >= days_per_month[month] * SECONDS_PER_DAY) {
        t -= days_per_month[month] * SECONDS_PER_DAY;
        if (month == 1 && is_leap_year(year)) {
            if (t < SECONDS_PER_DAY) break;
            t -= SECONDS_PER_DAY;
        }
        month++;
    }

    timeinfo.tm_mon = month;
    timeinfo.tm_mday = t / SECONDS_PER_DAY + 1;
    t %= SECONDS_PER_DAY;

    timeinfo.tm_hour = t / SECONDS_PER_HOUR;
    t %= SECONDS_PER_HOUR;

    timeinfo.tm_min = t / SECONDS_PER_MINUTE;
    timeinfo.tm_sec = t % SECONDS_PER_MINUTE;
    timeinfo.tm_isdst = 0;

    return &timeinfo;
}

struct tm *localtime(const time_t *timer) {
    return gmtime(timer); // assume UTC only
}

char *asctime(const struct tm *timeptr) {
    static char buffer[26];
    printf("%s %s %02d %02d:%02d:%02d %d\n",
           "SunMonTueWedThuFriSat" + 3 * timeptr->tm_wday,
           "JanFebMarAprMayJunJulAugSepOctNovDec" + 3 * timeptr->tm_mon,
           timeptr->tm_mday, timeptr->tm_hour, timeptr->tm_min, timeptr->tm_sec,
           timeptr->tm_year + 1900);
    return buffer;
}

char *ctime(const time_t *timer) {
    return asctime(localtime(timer));
}

time_t mktime(struct tm *timeptr) {
    time_t t = 0;

    // Convert broken-down time to calendar time
    for (int y = EPOCH_YEAR; y < timeptr->tm_year + 1900; y++) {
        t += days_in_year(y) * SECONDS_PER_DAY;
    }

    for (int m = 0; m < timeptr->tm_mon; m++) {
        t += days_per_month[m] * SECONDS_PER_DAY;
        if (m == 1 && is_leap_year(timeptr->tm_year + 1900)) {
            t += SECONDS_PER_DAY;
        }
    }

    t += (timeptr->tm_mday - 1) * SECONDS_PER_DAY;
    t += timeptr->tm_hour * SECONDS_PER_HOUR;
    t += timeptr->tm_min * SECONDS_PER_MINUTE;
    t += timeptr->tm_sec;

    return t;
}

clock_t clock(void) {
    // Dummy implementation, return arbitrary value
    return 0;
}

size_t strftime(char *s, size_t max, const char *format, const struct tm *timeptr) {
    // Simplified strftime
    printf("%02d/%02d/%04d %02d:%02d:%02d\n",
           timeptr->tm_mday, timeptr->tm_mon + 1, timeptr->tm_year + 1900,
           timeptr->tm_hour, timeptr->tm_min, timeptr->tm_sec);
    return strlen(s);
}

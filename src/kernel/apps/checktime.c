#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdint.h>
#include "drivers/ports.h"

// Register  Contents            Range
//  0x00      Seconds             0–59
//  0x02      Minutes             0–59
//  0x04      Hours               0–23 in 24-hour mode, 
//                                1–12 in 12-hour mode, highest bit set if pm
//  0x06      Weekday             1–7, Sunday = 1
//  0x07      Day of Month        1–31
//  0x08      Month               1–12
//  0x09      Year                0–99
//  0x32      Century (maybe)     19–20?
//  0x0A      Status Register A
//  0x0B      Status Register B
// If 0x32 doesn't give you the century, you can infer it from the year.

// I wrote this before I wrote the time.h implementation/interface.
// Since this is not a "real" OS, (or so to speak), we're just checking
// the time from the CMOS RTC. This behavior is implemented in QEMU x86, 
// and you just have to add this flag to sync/initialize the RTC, with
// yours: -rtc base=localtime or -rtc base=utc
#define CMOS_ADDRESS 0x70
#define CMOS_DATA 0x71

// Function to read from the CMOS RTC
unsigned int read_rtc_register(unsigned int reg) {
    outb(reg, CMOS_ADDRESS);
    return inb(CMOS_DATA);
}

// Function to convert BCD to decimal
unsigned int bcd_to_decimal(unsigned int bcd) {
    return (bcd & 0x0F) + ((bcd >> 4) * 10);
}

void get_time(unsigned int *hour, unsigned int *minute, unsigned int *second) {
    // Read the time registers
    *second = bcd_to_decimal(read_rtc_register(0x00));
    *minute = bcd_to_decimal(read_rtc_register(0x02));
    *hour = bcd_to_decimal(read_rtc_register(0x04));
}

int printtime(int argc, char **argv) {
    // if (ioperm(CMOS_ADDRESS, 2, 1) != 0) {
    //     printf("ioperm");
    //     return 1;
    // }
    unsigned int hour, minute, second;
    get_time(&hour, &minute, &second);
    printf("\n Current hour: %d, minute: %d, second: %d\n", hour, minute, second);
    //printf("\n Raw values: %d:%d:%d\n", hour, minute, second);
    printf("\n");

    return 0;
}
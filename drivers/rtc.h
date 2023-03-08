#ifndef __RTC_H__
#define __RTC_H__

#include "ports.h"
#include "screen.h"


struct rtc_t {
	unsigned char second;
	unsigned char minute;
	unsigned char hour;
	unsigned char day;
	unsigned char month;
	unsigned int year;

};

typedef struct rtc_t rtc;

void read_rtc(void);
#endif


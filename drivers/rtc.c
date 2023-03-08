#include "rtc.h"
#include "screen.h"

#define CURRENT_YEAR 2023

static int century_register = 0x00;
static unsigned char get_RTC_register(int reg);


static int get_update_in_progress_flag(void);

int get_update_in_progress_flag(void)
{
	port_byte_out(0x70, 0x0A);
	return (port_byte_in(0x71) & 0x80);	
}

unsigned char get_RTC_register(int reg)
{
	port_byte_out(0x70, reg);
	return port_byte_in(0x71);
}
void read_rtc(rtc *current_rtc) {
	unsigned char century;
	unsigned char last_second;
	unsigned char last_minute;
	unsigned char last_hour;
	unsigned char last_day;
	unsigned char last_month;
	unsigned char last_year;
	unsigned char last_century;
	unsigned char registerB;

	while (get_update_in_progress_flag())
		;
	current_rtc->second = get_RTC_register(0x00);	
	current_rtc->minute = get_RTC_register(0x02);
	current_rtc->hour = get_RTC_register(0x04);
	current_rtc->day = get_RTC_register(0x07);
	current_rtc->month = get_RTC_register(0x08);
	current_rtc->year = get_RTC_register(0x09);

	if (century_register != 0)
		century = get_RTC_register(century_register);

	do {
		last_second = current_rtc->second;
		last_minute = current_rtc->minute;
		last_hour = current_rtc->hour;
		last_day = current_rtc->day;
		last_month = current_rtc->month;
		last_year = current_rtc->year;
		last_century = century;

		while (get_update_in_progress_flag())
			;
		current_rtc->second = get_RTC_register(0x00);	
		current_rtc->minute = get_RTC_register(0x02);
		current_rtc->hour = get_RTC_register(0x04);
		current_rtc->day = get_RTC_register(0x07);
		current_rtc->month = get_RTC_register(0x08);
		current_rtc->year = get_RTC_register(0x09);

		if (century_register != 0)
			century = get_RTC_register(century_register);
	}while ((last_second != current_rtc->second) || (last_minute != current_rtc->minute) || (last_hour != current_rtc->hour) || (last_day != current_rtc->day) || (last_month != current_rtc->month) || (last_year != current_rtc->year) || (last_century != century));

	registerB = get_RTC_register(0x0B);

	if (!(registerB & 0x04)) {
		current_rtc->second = (current_rtc->second & 0x0f) + ((current_rtc->second / 16)*10);
		current_rtc->minute = (current_rtc->minute & 0x0f) + ((current_rtc->minute/ 16)*10);
		current_rtc->hour = ((current_rtc->hour & 0x0f) + (((current_rtc->hour & 0x70)/ 16)*10)) | (current_rtc->hour & 0x80);
		current_rtc->day = (current_rtc->day & 0x0f) + ((current_rtc->day / 16)*10);
		current_rtc->month = (current_rtc->month & 0x0f ) + ((current_rtc->month / 16) *10);
		current_rtc->year = (current_rtc->year & 0x0f) + ((current_rtc->year / 16) *10);
		if (century_register != 0)
			century = (century & 0x0f) + ((century / 16) *10);
	}

	if (!(registerB & 0x02) && (current_rtc->hour & 0x80))
		current_rtc->hour = ((current_rtc->hour & 0x7f) + 12) %24;

	if (century_register != 0)
		current_rtc->year += century *100;
	else {
		current_rtc->year += (CURRENT_YEAR / 100)*100;
		if (current_rtc->year < CURRENT_YEAR)
			current_rtc->year += 100;
	}
	k_printf("<0> RTC Read\n");
}

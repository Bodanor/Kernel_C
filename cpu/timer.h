#ifndef __TIMER_H__
#define __TIMER_H__

#include <stdint.h>

void init_timer(uint32_t freq);
void wait_timer(int ticks);
#endif

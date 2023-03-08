#ifndef __PCSPEAKER_H__
#define __PCSPEAKER_H__

#include <stdint.h>
#include "ports.h"

void beep_pc_speaker(uint32_t nFrequency, uint32_t time);
void stop_pc_speaker(void);
#endif

#include "pcspeaker.h"

void beep_pc_speaker(uint32_t nFrequency, uint32_t time)
{
	uint32_t Div;
	uint8_t tmp;

	Div = 1193180 / nFrequency;
	port_byte_out(0x43, 0xb6);
	port_byte_out(0x42, (uint8_t)(Div));
	port_byte_out(0x42, (uint8_t)(Div >> 8));

	tmp = port_byte_in(0x61);
	if (tmp != (tmp | 3))
		port_byte_out(0x61, tmp | 3);


}

void stop_pc_speaker(void)
{
	uint8_t tmp = port_byte_in(0x61) & 0xFC;
	port_byte_out(0x61, tmp);
}

#include "sys.h"

void shutdown(void)
{
    port_word_out(0x604, 0x2000);
}

void reboot()
{
    unsigned char good = 0x02;
    while (good & 0x02)
        good = port_byte_in(0x64);
    port_byte_out(0x64, 0xFE);
}
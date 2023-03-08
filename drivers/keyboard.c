#include "keyboard.h"
#include "ports.h"
#include "isr.h"
#include "screen.h"
#include "string.h"

#define BACKSPACE 0x0E
#define ENTER 0X1C
#define SC_MAX 57

static char key_buffer[256];

const char *sc_name[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6", 
    "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E", 
        "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl", 
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", 
        "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".", 
        "/", "RShift", "Keypad *", "LAlt", "Spacebar"};
const char sc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 
        'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G', 
        'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V', 
        'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};


void keyboard_callback(registers *regs)
{
	uint8_t scancode = port_byte_in(0x60);
	if (scancode > SC_MAX) return;

	else {
		char letter = sc_ascii[(int)scancode];
		k_print_chr(BLACK, WHITE, letter, -1, -1);
	}


}
void init_keyboard()
{
	register_int_handler(IRQ1, keyboard_callback);
}

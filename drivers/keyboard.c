#include "keyboard.h"
#include "ports.h"
#include "isr.h"
#include "screen.h"
#include "string.h"

#define SC_MAX 57

static char current_letter;
static uint32_t current_keymap;
volatile static int new_input;

const char sc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 
        'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G', 
        'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V', 
        'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};


void keyboard_callback(registers *regs)
{
	uint8_t scancode = port_byte_in(0x60);
	if (scancode > SC_MAX)
		return;
	
	else if (scancode == ENTER)
		current_letter = ENTER;
	else {
		current_letter = sc_ascii[(int)scancode];
	}
	new_input = 1;

}
void init_keyboard()
{
	register_int_handler(IRQ1, keyboard_callback);
	current_keymap = 0;
	new_input = 0;
}

char getLastInput(void)
{
	while (new_input == 0)
		;

	new_input = 0;
	return current_letter;
}

void set_keymap(uint32_t keymap)
{
	current_keymap = keymap;
}

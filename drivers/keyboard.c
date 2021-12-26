#include "keyboard.h"
#include "ports.h"
#include "../cpu/isr.h"
#include "screen.h"
#include "../libc/string.h"
#include "../kernel/kernel.h"
#include "../kernel/shell.h"


#define BACKSPACE 0x0E
#define ENTER 0x1C
#define SC_MAX 57

static char key_buffer[256];

const char *sc_name[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6", 
    "7", "8", "9", "0", "°", "-", "Backspace", "Tab", "A", "Z", "E", 
        "R", "T", "Y", "U", "I", "O", "P", "^", "$", "Enter", "Lctrl", 
        "Q", "S", "D", "F", "G", "H", "J", "K", "L", "M", "ù", "µ", 
        "LShift", "<", "", "X", "C", "V", "B", "N", ",", ";", ":", 
        "/", "RShift", "Keypad *", "LAlt", "Spacebar"};
const char sc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '+', '-', '?', '?', 'a', 'z', 'e', 'r', 't', 'y', 
        'u', 'i', 'o', 'p', '^', '$', '?', '?', 'q', 's', 'd', 'f', 'g', 
        'h', 'j', 'k', 'l', 'm', '\'', '`', '?', '\\', 'w', 'x', 'c', 'v', 
        'b', 'n', ',', '.', '/', '=', '?', '?', '?', ' '};

static void keyboard_callback(registers_t regs) {
    u8 scancode = port_byte_in(0x60);
    
    if (scancode > SC_MAX) return;
    if (scancode == BACKSPACE) {
        backspace(key_buffer);
        kprint_backspace();
    } else if (scancode == ENTER) {
        k_user_input('\n');
        k_print("\n");
        key_buffer[0] = '\0';
    } else {
        char letter = sc_ascii[(int)scancode];
        /* Remember that kprint only accepts char[] */
        char str[2] = {letter, '\0'};
        append(key_buffer, letter);
        k_user_input(letter);
        k_print(str);
    }

}

void init_keyboard() {
   register_interrupt_handler(IRQ1, keyboard_callback);
}
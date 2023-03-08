#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <stdint.h>

#define US_KEYMAP 0
#define BE_KEYMAP 1
#define FR_KEYMAP 2

#define BACKSPACE 0x0E
#define ENTER 0X1C

void init_keyboard(void);
char getLastInput(void);
void set_keymap(uint32_t keymap);
#endif

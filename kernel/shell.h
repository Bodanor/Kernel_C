#ifndef __SHELL_H__
#define __SHELL_H__

#include <stdint.h>
#include "keyboard.h"
#include "screen.h"

#define USER_MAX_INPUT 256

void init_shell(void);
void shell_loop(void);
#endif

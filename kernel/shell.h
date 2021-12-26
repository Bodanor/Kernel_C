#ifndef __SHELL_H__
#define __SHELL_H__

#include "../drivers/screen.h"
#include "../libc/string.h"
#include "../libc/misc.h"
#include "../libc/sys.h"

char *k_shell_prompt(const char *hostname);
void k_shell_verify_cmd(char *input);
void k_user_input(char c);
#endif
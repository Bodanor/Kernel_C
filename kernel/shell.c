#include "shell.h"
#include "keyboard.h"
#include "screen.h"

#define DEBUG __asm__("xchgw %bx, %bx")
static char user_input[USER_MAX_INPUT];

static void shell_prompt(void);
static void shell_input(void);

void init_shell()
{
	set_keymap(BE_KEYMAP);
}

void shell_prompt(void)
{
	k_print_string(BLACK, WHITE, "Kernel #~ :", -1, -1);

}

void shell_loop()
{

	while (1) {
		shell_prompt();
		shell_input();		
		if (strcmp(user_input, "SHUTDOWN") == 0) {

		}
		else if (strcmp(user_input, "REBOOT") == 0) {

		}
		else{
			k_print_string(BLACK, RED, "Command not found !\n", -1, -1);
		}
	}
	

}

void shell_input(void)
{
	int c;
	char *user_input_pt = &user_input[0];

	while ((c = getLastInput()) != ENTER) {
		if (c == BACKSPACE) {
			if (user_input_pt != &user_input[0]) {
				*--user_input_pt = '\0';
				k_print_backspace();
				}
			else {
				// Beep sound soon 
			}
		}
		else {

			k_print_chr(BLACK, WHITE, c, -1, -1);
			*user_input_pt++ = c;
		}
	}
	*user_input_pt++ = '\0';
	k_print_chr(BLACK, WHITE, '\n', -1,-1);
}

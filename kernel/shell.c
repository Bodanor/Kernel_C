#include "shell.h"
#include "rtc.h"
#include "screen.h"

#define DEBUG __asm__("xchgw %bx, %bx")

extern rtc boot_rtc_time;

static char user_input[USER_MAX_INPUT];

static void shell_prompt(void);
static void shell_input(void);

static void uptime_command(void);
void init_shell()
{
	set_keymap(BE_KEYMAP);
}

void shell_prompt(void)
{
	k_printf("%s", "Kernel #~ : ");
}

void shell_loop()
{

	while (1) {
		shell_prompt();
		shell_input();		
		if (*user_input != '\0') {
			if (strcmp(user_input, "SHUTDOWN") == 0) {

			}
			else if (strcmp(user_input, "REBOOT") == 0) {

			}
			else if (strcmp(user_input, "CLEAR") == 0){
				k_print_clear_screen();
			}
			else if (strcmp(user_input, "UPTIME") == 0) {
				uptime_command();
			}
			else{
				k_print_string(BLACK, RED, "Command not found !\n", -1, -1);
			}
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
				beep_pc_speaker(1000, 10);
				wait_timer(4);
				stop_pc_speaker();
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

void uptime_command(void)
{
	rtc current_rtc_time;
	rtc uptime_rtc;
	read_rtc(&uptime_rtc);
	
	uint32_t boot_uptime_seconds;
	uint32_t current_uptime_seconds;

	boot_uptime_seconds = boot_rtc_time.second + (boot_rtc_time.minute *60) + (boot_rtc_time.hour *3600) + (boot_rtc_time.day*86400);
	current_uptime_seconds = uptime_rtc.second + (uptime_rtc.minute * 60) + (uptime_rtc.hour * 3600) + (uptime_rtc.day * 86400);
	
	uptime_rtc.second = (current_uptime_seconds - boot_uptime_seconds) % 60;
	uptime_rtc.minute = (current_uptime_seconds - boot_uptime_seconds) / 60;
	uptime_rtc.hour = (current_uptime_seconds - boot_uptime_seconds) / 3600;
	uptime_rtc.day = (current_uptime_seconds - boot_uptime_seconds) / 86400;

	k_printf("Uptime since boot: %d days, %d hours, %d minutes, %d seconds\n", uptime_rtc.day, uptime_rtc.hour, uptime_rtc.minute, uptime_rtc.second);

}


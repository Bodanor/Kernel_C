#ifndef __SCREEN_H__
#define __SCREEN_H__
#define VIDEO_ARRAY 0xb8000;

#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

#define MAX_ROWS 25
#define MAX_COLS 80

void k_clear_screen();
void k_print_welcome_label(int colour, const char *str);
void k_print_operation_status (int type, const char *str);
void k_print(const char *str);
void k_print_colour(int colour, const char *str);

#endif
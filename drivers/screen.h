#ifndef __SCREEN_H__
#define __SCREEN_H__
#define VIDEO_ARRAY 0xb8000;

#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

#define MAX_ROWS 25
#define MAX_COLS 80



enum error_types {error = 4, success = 2, warning = 14, info = 1, def = 15};

void k_clear_screen();
void k_print_welcome_label(const char *version, int color_version, const char *dev, int color_dev);
void k_print_operation_status (int type, const char *str);
void k_print(const char *str);
void k_print_colour(int col, int row , const char *str, int attr);
void set_background(int attr);
void kprint_backspace();
int k_print_char(int col, int row , const char c, int attr);
#endif
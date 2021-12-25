#include "screen.h"
#include "ports.h"

int get_cursor_offset();
void set_cursor_offset(int offset);
int k_print_char(int col, int row , const char c, int attr);
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);


void kprint_backspace() {
    int offset = get_cursor_offset()-2;
    int row = get_offset_row(offset);
    int col = get_offset_col(offset);
    k_print_char( col, row, 0x08, 0x0f);
}

int get_cursor_offset() {
    /* Use the VGA ports to get the current cursor position
     * 1. Ask for high byte of the cursor offset (data 14)
     * 2. Ask for low byte (data 15)
     */
    port_byte_out(REG_SCREEN_CTRL, 14);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8; /* High byte: << 8 */
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);
    return offset * 2; /* Position * size of character cell */
}

void set_cursor_offset(int offset) {
    /* Similar to get_cursor_offset, but instead of reading we write data */
    offset /= 2;
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

int get_offset(int col, int row) { return 2 * (row * MAX_COLS + col); }
int get_offset_row(int offset) { return offset / (2 * MAX_COLS); }
int get_offset_col(int offset) { return (offset - (get_offset_row(offset)*2*MAX_COLS))/2; }

void k_clear_screen() {
    int screen_size = MAX_COLS * MAX_ROWS;
    int i;
    char *screen = (char*)VIDEO_ARRAY;

    for (i = 0; i < screen_size; i++) {
        screen[i*2] = '\0';
        screen[i*2+1] = 0xf;
    }
    set_cursor_offset(get_offset(0, 0));
}

int k_print_char(int col, int row , const char c, int attr)
{
    unsigned char *video_memory = (unsigned char*) VIDEO_ARRAY;

    int offset;
    if (col >= 0 && row >= 0)
        offset = get_offset(col, row);
    else
        offset = get_cursor_offset();
    
    if (c == '\n')
    {
        row = get_offset_row(offset);
        offset = get_offset(0, row+1);
    }
    else if (c == 0x08) { /* Backspace */
        video_memory[offset] = ' ';
        video_memory[offset+1] = attr;
    }
    else
    {
        video_memory[offset] = c;
        video_memory[offset + 1] = attr;
        offset += 2;
    }
    set_cursor_offset(offset);
    return offset;

}

void k_print_colour(int col, int row, const char *str, int attr)
{
    int offset;
    if (col >= 0 && row >= 0)
        offset = get_offset(col, row);
    
    else
    {
        offset = get_cursor_offset();
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }
    while (*str != '\0')
    {
        offset = k_print_char(col, row, *str++, attr);
        col = get_offset_col(offset);
        row = get_offset_row(offset);
    }
}

void k_print(const char *str)
{
    k_print_colour(-1, -1, str, 0x0f);
}

void k_print_operation_status (int type, const char *str)
{
    k_print("[ ");
    switch (type)
    {
        case error:
            k_print_colour(-1, -1, "FAIL", type);
            break;
        case success:
            k_print_colour(-1, -1, "SUCCESS", type);
            break;
        case warning:
            k_print_colour(-1, -1, "WARNING", type);
            break;
        case info:
            k_print_colour(-1, -1, "INFO", type);
            break;

    }
    k_print(" ] ");
    k_print(str);
    k_print_char(-1,-1, '\n', def);
}

void k_print_welcome_label(const char *version, int color_version, const char *dev, int color_dev)
{
    k_print_char(-1, -1, '[', def);
    k_print_char(-1, -1, ' ', color_version);
    k_print_colour(-1, -1, version, color_version);
    k_print_char(-1, -1, ' ', color_version);
    k_print_char(-1, -1, ']', def);
    k_print_char(-1, -1, ' ', def);

    k_print_char(-1, -1, '[', def);
    k_print_char(-1, -1, ' ', color_dev);
    k_print_colour(-1, -1, dev, color_dev);
    k_print_char(-1, -1, ' ', color_dev);

    k_print("]\n\n");

}

/*
 *change the lsat instruction to only modify the second byte without
 * touching the first one
*/
void set_background(int attr)
{
    unsigned char *videomemory = (unsigned char*)VIDEO_ARRAY;
    int i;
    for (i = 0; i < MAX_COLS* MAX_ROWS; i++)
    {
        *(videomemory + i *2 + 1) = (attr = attr | (1 << 4));
    }
}
#define VGA_ADRESS 0XB8000
#define BLACK 0
#define GREEN 2
#define RED 4
#define YELLOW 14
#define WHITE 15

unsigned short *terminal_buffer;
unsigned int vga_index;

void clear_screen(void)
{
    int index = 0;
    while (index < 80 * 25 *2)
        terminal_buffer[index+=2] = ' ';
}

void print_string(char *str, unsigned char color)
{
    while (*str)
    {
        terminal_buffer[vga_index] = *str |color << 8;
        str++;
        vga_index++;
    }
}

void main(void)
{
    terminal_buffer = (unsigned short*)VGA_ADRESS;
    vga_index = 0;
    clear_screen();
    print_string("Hello World !", YELLOW);
    vga_index = 80;
    print_string("It's my first kernel !", RED);
}
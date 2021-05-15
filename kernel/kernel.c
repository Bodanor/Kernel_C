#include "../include/kernel.h"
#include "../include/utils.h"

unsigned char g_fore_color,  g_back_color;

unsigned short vga_entry(unsigned char ch, uint8 fore_color, uint8 back_color) 
{
  unsigned short ax = 0;
  unsigned char ah = 0, al = 0;

  ah = back_color;
  ah <<= 4;
  ah |= fore_color;
  ax = ah;
  ax <<= 8;
  al = ch;
  ax |= al;

  return ax;
}

void clear_screen(void)
{
    int index = 0;
    while (index < 80 * 25 *2)
        terminal_buffer[index++] = vga_entry(NULL, g_fore_color, g_back_color);
    
    vga_index = 0;
}

void init_vga(unsigned char fore_color, unsigned char back_color)
{
  terminal_buffer = (unsigned short*)VGA_ADDRESS;
  g_fore_color = fore_color;
  g_back_color = back_color;
  vga_index = 0;
  clear_screen();

}


void print_string_color(char *str, unsigned char color)
{
    while (*str)
    {
        terminal_buffer[vga_index] = vga_entry(*str, color, g_back_color);
        str++;
        vga_index++;
    }
}
// TODO: Short this function if we can by only having one if condition for '\n'
void print_string(char *str)
{
  unsigned int string_len = str_len(str);

  while (*str != '\0')
    {
      if (*str == '\n')
      {
        vga_index += (80 - string_len);
        str++;
      }
      else{
      terminal_buffer[vga_index++] = vga_entry(*str, g_fore_color, g_back_color);
      str++;
      }
    }

}

void main(void)
{
    char *kernel_ver = "Kernel version 0.0.1 !\n";
    char *second_line = "Hello World !\n";
    init_vga(WHITE, BLUE);
    print_string(kernel_ver);
    print_string(second_line);
}
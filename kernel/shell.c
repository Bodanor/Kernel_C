#include "shell.h"

static char key_buffer[256];

char *k_shell_prompt(const char *hostname)
{
    k_print(hostname);

    while (1)
    {
        for (int i = 0; i < 256; i++)
        {
            if (key_buffer[i] == '\n')
            {
                key_buffer[i] = '\0';
                return key_buffer;
            }
        }
    }
}

void k_shell_verify_cmd(char *input)
{
    if (strcmp("tree", input) == 0)
        draw_tree();
    else if (strcmp("clear", input) == 0)
        k_clear_screen();

    else if (strcmp("shutdown", input) == 0 || strcmp ("halt", input) == 0 || strcmp("poweroff", input) == 0)
        shutdown();
    
    else if (strcmp("reboot", input) == 0)
        reboot();
    
    else if (*input != '\0')
    {
        k_print_colour(-1, -1, input, 0x0f);
        k_print_colour(-1, -1, " : Command not found\n", 0x0f);
    }

    memory_set(key_buffer, 0, 256);
    
}

void k_user_input(char c)
{
    append(key_buffer, c);
    
}
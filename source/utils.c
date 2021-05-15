#include "../include/utils.h"

unsigned int str_len(const char *string)
{
    const char *tmp;
    for (tmp = string; *tmp != '\0' && *tmp != '\n'; ++tmp)
        ;
    

    return tmp - string;

}
#include "misc.h"

void draw_tree(void)
{
    int i,j;
    for(i=1; i<=12; i++)
    {
        for(j=1;j<=12-i; j++)
        {
            k_print(" ");
        }
        for(j=1; j<=2*i-1; j++)
        {
            k_print("*");
        }
        k_print("\n");
    }
    
}
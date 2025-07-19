#include "atoi_split.h"

int *ft_atoi_split(char *str)
{
    static int tab[16];
    int i;

    i = 0;
    while (*str && i < 16)
    {
        if (*str >= '0' && *str <= '9')
        {
            tab[i] = *str - 48;
            i++;
        }
        else if (*str == '-')
            return 0;
        str++;
    }
    return (tab);
}
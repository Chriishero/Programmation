#include <stdio.h>

char *ft_strncpy(char *dest, char *src, unsigned int n)
{
    while (*dest | *src)
    {
        if (n > 0)
        {
            *dest = *src;
        }
        else
        {
            *dest = '\0';
        }
        *dest++;
        *src++;
        n--;
    }
    return dest;
}
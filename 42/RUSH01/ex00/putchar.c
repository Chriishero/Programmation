#include <unistd.h>
#include "putchar.h"

void ft_putchar(char c)
{
    write(1, &c, 1);
}
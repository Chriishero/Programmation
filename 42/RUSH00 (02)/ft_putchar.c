#include <unistd.h>
#include "ft_putchar.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

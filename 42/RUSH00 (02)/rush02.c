#include "ft_putchar.h"
#include "rush02.h"
#include <stdio.h>

void	put_rectangle_element(int i, int x, int y)
{
	if (i == 1 || i == x)
	{
		ft_putchar('A');
	}
	else if (i == x * (y - 1) + 1 || i == x * y)
	{
		ft_putchar('C');
	}
	else if ((i - 1) % x == 0 || i % x == 0 || i <= x || i >= x * (y - 1))
	{
		ft_putchar('B');
	}
	else
	{
		ft_putchar(' ');
	}
	if (i % x == 0)
	{
		ft_putchar('\n');
	}
}

void	rush(int x, int y)
{
	int	i;

	i = 1;
	while (i <= x * y)
	{
		put_rectangle_element(i, x, y);
		i++;
	}
}

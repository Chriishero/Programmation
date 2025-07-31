/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvillene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:41:37 by cvillene          #+#    #+#             */
/*   Updated: 2025/07/21 15:20:26 by cvillene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
/*
void	ft_putnbr(int nb)
{
	char	buffer[13];
	int		i;
	int		negative;

	i = 1;
	negative = (nb < 0);
	if (negative)
		nb *= -1;
	if (nb == 0)
		buffer[i] = '0';
	while (nb > 0)
	{
		buffer[i] = nb % 10 + '0';
		nb /= 10;
		i++;
	}
	if (negative)
		buffer[i] = '-';
	while (i > 0)
	{
		write(1, &buffer[i], 1);
		i--;
	}
}*/
void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nb)
{
	if (nb == -2147483648)
		write(1, "-2147483648", 11);
	else if (nb < 0)
	{
		ft_putchar('-');
		ft_putnbr(-nb);
	}
	else if (nb <= 9)
		ft_putchar(nb + '0');
	else
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
}
/*
int main(void)
{
	ft_putnbr(-452);
	return 0;
}*/

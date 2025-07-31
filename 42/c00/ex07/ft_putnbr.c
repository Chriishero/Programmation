/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvillene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 22:24:45 by cvillene          #+#    #+#             */
/*   Updated: 2025/07/09 22:27:16 by cvillene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr(int nb)
{
	char	buffer[12];
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
		buffer[i] = (nb % 10) + '0';
		nb /= 10;
		i++;
	}
	if (negative)
		buffer[i++] = '-';
	while (i > 0)
	{
		write(1, &buffer[i], 1);
		i--;
	}
}

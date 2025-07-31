/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvillene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:06:35 by cvillene          #+#    #+#             */
/*   Updated: 2025/07/25 08:28:08 by cvillene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_iterative_power(int nb, int power)
{
	int	a;

	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	a = nb;
	while (power > 1)
	{
		nb *= a;
		power--;
	}
	return (nb);
}
/*
#include <stdio.h>

int	main(void)
{
	printf("%d", ft_iterative_power(5, 3));
	return (0);
}*/

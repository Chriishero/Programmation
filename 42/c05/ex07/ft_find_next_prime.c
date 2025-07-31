/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_next_prime.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvillene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 10:43:08 by cvillene          #+#    #+#             */
/*   Updated: 2025/07/24 09:00:17 by cvillene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_prime(int nb)
{
	int	i;

	if (nb < 2)
		return (0);
	i = 2;
	while (i < nb)
		if (nb % i++ == 0)
			return (0);
	return (1);
}

int	ft_find_next_prime(int nb)
{
	int	prime;

	prime = 0;
	while (!prime)
		prime = ft_is_prime(nb++);
	return (nb - 1);
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%d", ft_find_next_prime(34));
	return (0);
}*/

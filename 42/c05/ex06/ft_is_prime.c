/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_prime.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvillene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 10:30:27 by cvillene          #+#    #+#             */
/*   Updated: 2025/07/23 13:22:53 by cvillene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_prime(int nb)
{
	int	i;

	if (nb == 1 || nb == 0)
		return (0);
	i = 2;
	while (i < nb)
	{
		if (nb % i++ == 0)
			return (0);
	}
	return (1);
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%d", ft_is_prime(7));
	return (0);
}*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvillene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:03:00 by cvillene          #+#    #+#             */
/*   Updated: 2025/07/16 14:07:22 by cvillene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>*/

int	ft_iterative_factorial(int nb)
{
	int	i;
	int	n;

	i = 1;
	n = 1;
	while (i <= nb)
	{
		n *= i++;
	}
	return (n);
}
/*
int	main(void)
{
	printf("%d", ft_iterative_factorial(5));
	return (0);
}*/

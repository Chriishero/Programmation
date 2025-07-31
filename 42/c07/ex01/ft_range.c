/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvillene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 08:15:57 by cvillene          #+#    #+#             */
/*   Updated: 2025/07/23 14:34:47 by cvillene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	*ft_range(int min, int max)
{
	int	i;
	int	*tab;

	if (min >= max)
		return (NULL);
	tab = (int *)malloc(sizeof(int) * (max - min + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (min < max)
	{
		tab[i] = min++;
		i++;
	}
	return (tab);
}
/*
#include <stdio.h>

int	main(void)
{
	int	*tab;
	
	tab = ft_range(9, 5);	
	if (tab)
	{
		for (int i = 0; tab[i]; i++)
			printf("%d", tab[i]);
		free(tab);
	}
	return (0);
}*/

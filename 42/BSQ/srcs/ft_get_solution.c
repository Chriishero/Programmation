/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_solution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvillene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 17:41:26 by cvillene          #+#    #+#             */
/*   Updated: 2025/07/30 19:29:58 by cvillene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_rows(char *map)
{
	int	i;
	int	count;
	
	i = 0;
	while (map[i])
	{
		if (map[i] == '\n')
			count++;
		i++;
	}
	return (count);
}

int	ft_count_columns(char *map)
{
	int	count;

	i = 0;
	while (map[i] != '\n')
		i++;
	return (i);
}

char	**

char	*ft_get_solution(char* map)
{
	int	row;
	int	col;
	char	**matrix;

	area = 0;
	row = 0;
	matrix = ft_getmatrix(map, ft_count_rows(map), ft_count_columns(map));
	while (row <= ft_count_rows(map))
	{
		col = 0;
		while (col <= ft_count_columns(map))
		{
			
		}
	}
}

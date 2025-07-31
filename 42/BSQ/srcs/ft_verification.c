/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verification.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvillene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:06:55 by cvillene          #+#    #+#             */
/*   Updated: 2025/07/30 17:35:07 by cvillene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_is_firstline_valid(char *map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i] >= '0' && map[i] <= '9')
		i++;
	if (i == 0)
		return (-1);
	j = i;
	while (j - i < 3)
	{
		if (map[j] < 32 && map[j] > 126)
		{
			printf("mueheheh : %c", map[j]);
			return (-1);
		}
		if (ft_strnchar(map, i + 3, map[j], j))
			return (-1);
		j++;
	}
	if (map[j] != '\n')
	{
		printf("oui : %c", map[j]);
		return (-1);
	}
	return (0);
}

int	ft_is_len_valid(char *map)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (map[i] != '\n')
		i++;
	j = 1;
	while (map[i + j] != '\n')
		j++;
	k = 1;
	while (map[i + j * k])
	{
		if (map[i + j * k] != '\n')
			return (-1);
		k++;
	}
	if (k - 1 != ft_atoi(map))
		return (-1);
	return (0);
}

int	ft_map_has_box(char *map)
{
	char	box;
	int		i;

	i = 0;
	while (map[i] >= '0' && map[i] <= '9')
		i++;
	box = map[i + 1];
	while (map[i] != '\n')
		i++;
	while (map[i])
	{
		if (map[i] == box)
			return (0);
		i++;
	}
	return (-1);
}

int	ft_is_characters_valid(char *map)
{
	int	i;
	int	j;
	int	len_line;
	int	void_c;

	i = 0;
	while (map[i] != '\n')
		i++;
	len_line = i + 1;
	while (map[len_line] != '\n')
		len_line++;
	void_c = 0;
	while (map[void_c] >= '0' && map[void_c] <= '9')
		void_c++;
	len_line -= i;
	j = i + 1;
	while (map[i + j])
	{
		if (map[i + j] != map[void_c] && map[i + j] != map[void_c + 1]
			&& j % len_line != 0)
			return (-1);
		j++;
	}
	return (0);
}

int	ft_is_map_valid(char *map)
{
	if (ft_is_firstline_valid(map) == -1)
	{
		ft_putstr("firstline");
		return (-1);
	}
	if (ft_is_len_valid(map) == -1)
	{
		ft_putstr("len");
		return (-1);
	}
	if (ft_map_has_box(map) == -1)
	{
		ft_putstr("box");
		return (-1);
	}
	if (ft_is_characters_valid(map) == -1)
	{
		ft_putstr("characters");
		return (-1);
	}
	return (0);
}

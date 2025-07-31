/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvillene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 08:13:15 by cvillene          #+#    #+#             */
/*   Updated: 2025/07/25 08:57:21 by cvillene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_index_of(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_revstr(char *str)
{
	int		i;
	int		j;
	char	*reverse;

	reverse = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
	i = ft_strlen(str);
	j = 0;
	while (--i >= 0)
	{
		reverse[j] = str[i];
		j++;
	}
	reverse[j] = '\0';
	return (reverse);
}

int	ft_char_in_str(char c, char *str)
{
	while (*str)
		if (c == *str++)
			return (0);
	return (1);
}

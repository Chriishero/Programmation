/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvillene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:59:10 by cvillene          #+#    #+#             */
/*   Updated: 2025/07/30 08:39:29 by cvillene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void    ft_putstr(char *str)
{
	int     i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	ft_atoi(char *nbr)
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	while (nbr[i] == ' ' || (nbr[i] >= 7 && nbr[i] <= 13))
		i++;
	if (nbr[i] < '0' || nbr[i] > '9')
	{
		ft_puterror("", nbr, 2);
		return (-1);
	}
	while (nbr[i] >= '0' && nbr[i] <= '9')
	{
		n = n * 10 + (nbr[i] - '0');
		i++;
	}
	return (n);
}

int	ft_tabstrlen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

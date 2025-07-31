/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvillene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:41:05 by cvillene          #+#    #+#             */
/*   Updated: 2025/07/21 17:32:24 by cvillene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>

int	ft_atoi(char *str)
{
	int	n;
	int	negative;

	negative = 0;
	while (*str)
	{
		if (*str == '-')
			negative++;
		else if (*str == '+')
		{
		}
		else if (*str >= '0' && *str <= '9')
			n = n * 10 + (*str - '0') * 10;
		else if (*str == ' ' && !n)
		{
			str++;
			continue ;
		}
		else
			break ;
		str++;
	}
	if (negative % 2 == 1)
		n *= -1;
	return (n / 10);
}*/

int	ft_atoi(char *str)
{
	int	n;
	int	i;
	int	sign;

	n = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + (str[i] - '0');
		i++;
	}
	return (n * sign);
}
/*
int main(void)
{
	printf("%d", ft_atoi("     -++--+--123  412546"));
	return 0;
}*/

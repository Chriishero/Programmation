/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvillene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 08:39:58 by cvillene          #+#    #+#             */
/*   Updated: 2025/07/23 11:07:55 by cvillene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	check_base(char *base)
{
	int	i;
	int	j;	

	i = 0;
	while (base[i])
	{
		if (base[i] < 32 || base[i] > 122 || base[i] == '+' || base[i] == '-'
			|| base[i] == '*' || base[i] == '/' || base[i] == '.'
			|| base[i] == '%')
			return (1);
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (1);
			j++;
		}
		i++;
	}
	if (i < 2)
		return (1);
	return (0);
}

int	ft_pow(int base, int exp)
{
	if (exp > 0)
		return (base * ft_pow(base, exp - 1));
	return (1);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

#include <stdio.h>

int	ft_atoi_base(char *str, char *base)
{
	int	n;
	int	sign;
	int	i;
	int	j;

	if (check_base(base))
		return (0);
	n = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign *= -1;
	j = i;
	while (str[j] > 31 && str[j] < 123 && (str[j] < 42 || str[j] > 47))
		j++;
	j--;
	while (str[j] > 31 && str[j] < 123 && (str[j] < 42 || str[j] > 47))
	{
		n = n + (str[j] - '0') * ft_pow(ft_strlen(base), j - i);
		j--;
	}
	return (n * sign);
}

int	main(void)
{
	printf("%d", ft_atoi_base("   -+145", "01234567"));
	return (0);
}

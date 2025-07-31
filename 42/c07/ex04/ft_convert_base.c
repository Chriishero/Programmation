/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvillene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:42:03 by cvillene          #+#    #+#             */
/*   Updated: 2025/07/25 08:55:46 by cvillene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		ft_strlen(char *str);
int		ft_index_of(char c, char *str);
char	*ft_revstr(char *str);
int		ft_char_in_str(char c, char *str);

char	*ft_check_and_minimize_n(char *nbr, char *base_from)
{
	int		sign;
	char	*new_nbr;
	char	*result;

	new_nbr = (char *)malloc(sizeof(char) * ft_strlen(nbr) + 1);
	if (!new_nbr)
		return (NULL);
	result = new_nbr;
	while (*nbr == ' ' || (*nbr >= 7 && *nbr <= 13))
		nbr++;
	sign = 1;
	while (*nbr == '+' || *nbr == '-')
		if (*nbr++ == '-')
			sign *= -1;
	if (sign < 0)
		*new_nbr++ = '-';
	else
		*new_nbr++ = '+';
	while (!ft_char_in_str(*nbr, base_from) && *nbr)
		*new_nbr++ = *nbr++;
	*new_nbr++ = '\0';
	return (result);
}

int	check_base(char *base)
{
	int	i;
	int	j;

	i = 0;
	while (base[i])
	{
		if (base[i] < 32 || base[i] > 122 || base[i] == '+' || base[i] == '-')
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

char	*value_to_representation(int n, char *base_from)
{
	int		i;
	int		sign;
	char	*digits;

	if (n == 0)
		return ((char *[]){(char []){base_from[0], '\0'}}[0]);
	digits = (char *)malloc(sizeof(char) * 33 + 1);
	i = 0;
	if (n < 0)
	{
		n *= -1;
		sign = -1;
	}
	while (n > 0)
	{
		digits[i] = base_from[n % ft_strlen(base_from)];
		n /= ft_strlen(base_from);
		i++;
	}
	if (sign < 0)
		digits[i] = '-';
	i++;
	digits[i] = '\0';
	return (digits);
}

int	representation_to_value(char *digits, char *base_to)
{
	int	len_base;
	int	n;
	int	i;

	len_base = ft_strlen(base_to);
	n = 0;
	i = 1;
	while (digits[i])
	{
		n = len_base * n + ft_index_of(digits[i], base_to);
		i++;
	}
	if (digits[0] == '-')
		n *= -1;
	return (n);
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	int		value;
	char	*new_nbr;

	if (check_base(base_from) || check_base(base_to))
		return (NULL);
	new_nbr = ft_check_and_minimize_n(nbr, base_from);
	value = representation_to_value(new_nbr, base_from);
	new_nbr = value_to_representation(value, base_to);
	return (ft_revstr(new_nbr));
}
/*
#include <stdio.h>
int	main(int argc, char **argv)
{
	if (argc > 3)
		printf("%s", ft_convert_base(argv[1], argv[2], argv[3]));
	return (0);
}*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnbr_base.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvillene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 08:14:02 by cvillene          #+#    #+#             */
/*   Updated: 2025/07/23 08:37:12 by cvillene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

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

void	ft_putnbr_base(int nbr, char *base)
{
	int	len_base;

	if (check_base(base))
		return ;
	if (nbr < 0)
	{
		ft_putchar('-');
		nbr *= -1;
	}
	len_base = 0;
	while (base[len_base])
		len_base++;
	if (nbr < len_base)
		ft_putchar(base[nbr]);
	else
	{
		ft_putnbr_base(nbr / len_base, base);
		ft_putnbr_base(nbr % len_base, base);
	}
}
/*
int	main(void)
{
	ft_putnbr_base(547, "01");
	return (0);
}*/

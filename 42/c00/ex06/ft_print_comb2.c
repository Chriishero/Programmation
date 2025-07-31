/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_comb2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvillene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 22:04:12 by cvillene          #+#    #+#             */
/*   Updated: 2025/07/09 22:19:46 by cvillene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	write_c(int i, int j)
{
	char	i1;
	char	i2;
	char	j1;
	char	j2;

	i1 = i / 10 + '0';
	i2 = i % 10 + '0';
	write(1, &i1, 1);
	write(1, &i2, 1);
	write(1, " ", 1);
	j1 = j / 10 + '0';
	j2 = j % 10 + '0';
	write(1, &j1, 1);
	write(1, &j2, 1);
}

void	ft_print_comb2(void)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 99)
	{
		while (j <= 99)
		{
			if (j > i)
			{
				write_c(i, j);
				if (i != 98 || j != 99)
				{
					write(1, ", ", 2);
				}
			}
			j++;
		}
		i++;
		j = i + 1;
	}
}

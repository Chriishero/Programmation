/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvillene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 07:59:46 by cvillene          #+#    #+#             */
/*   Updated: 2025/07/18 09:16:38 by cvillene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_rev_params(char **params)
{
	int		i;
	char	*str;

	i = 0;
	while (*params)
	{
		i++;
		params++;
	}
	while (*--params && i-- > 1)
	{
		str = *params;
		while (*str)
		{
			write(1, str, 1);
			str++;
		}
		write(1, "\n", 1);
	}
}

int	main(int argc, char *argv[])
{
	if (argc > 0)
		ft_rev_params(argv);
	return (0);
}

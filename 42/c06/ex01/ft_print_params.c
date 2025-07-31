/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_params.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvillene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 07:46:10 by cvillene          #+#    #+#             */
/*   Updated: 2025/07/18 09:16:12 by cvillene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_print_params(char **params)
{
	char	*str;

	params++;
	while (*params)
	{
		str = *params;
		while (*str)
		{
			write(1, str, 1);
			str++;
		}
		write(1, "\n", 1);
		params++;
	}
}

int	main(int argc, char *argv[])
{
	if (argc > 0)
		ft_print_params(argv);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvillene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 08:19:34 by cvillene          #+#    #+#             */
/*   Updated: 2025/07/18 09:17:10 by cvillene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int	ft_strcmp(char *str1, char *str2)
{
	int	cmp;
	int	i;

	cmp = 0;
	i = 0;
	while (str1[i] && str2[i])
	{
		cmp += (str1[i] - str2[i]);
		i++;
	}
	return (cmp);
}

void	ft_sort_params(char **params)
{
	int		sorted;
	int		len;
	int		i;
	char	*temp;

	len = 0;
	while (params[len])
		len++;
	sorted = 0;
	while (!sorted)
	{
		i = 0;
		sorted = 1;
		while (i + 1 < len)
		{
			if (ft_strcmp(params[i], params[i + 1]) > 0)
			{
				sorted = 0;
				temp = params[i];
				params[i] = params[i + 1];
				params[i + 1] = temp;
			}
			i++;
		}
	}
}

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
	{
		ft_sort_params(argv);
		ft_print_params(argv);
	}
	return (0);
}

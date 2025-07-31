/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvillene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:03:05 by cvillene          #+#    #+#             */
/*   Updated: 2025/07/29 15:25:56 by cvillene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_sort(int *tab, int length, int (*f)(int, int))
{
	int	cmp;
	int	order;
	int	i;

	order = 0;
	i = 0;
	while (i < length - 1)
	{
		cmp = (*f)(tab[i], tab[i + 1]);
		if (order == 0 && cmp != 0)
		{
			if (cmp < 0)
				order = 1;
			else
				order = -1;
		}
		else if ((order == 1 && cmp > 0) || (order == -1 && cmp < 0))
			return (0);
		i++;
	}
	return (1);
}

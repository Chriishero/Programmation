/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvillene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:30:15 by cvillene          #+#    #+#             */
/*   Updated: 2025/07/29 14:49:28 by cvillene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_puterr(char err)
{
	if (err == '/')
		ft_putstr("Stop : division by zero\n");
	else if (err == '%')
		ft_putstr("Stop : modulo by zero\n");
}

void	ft_do_op(int val1, char operator, int val2)
{
	if (val2 == 0 && (operator == '/' || operator == '%'))
	{
		ft_puterr(operator);
		return ;
	}
	if (operator == '+')
		ft_putnbr(val1 + val2);
	else if (operator == '-')
		ft_putnbr(val1 - val2);
	else if (operator == '*')
		ft_putnbr(val1 * val2);
	else if (operator == '/')
		ft_putnbr(val1 / val2);
	else if (operator == '%')
		ft_putnbr(val1 % val2);
	else
		ft_putstr("0");
}

int	main(int argc, char **argv)
{
	if (argc == 4)
		ft_do_op(ft_atoi(argv[1]), argv[2][0], ft_atoi(argv[3]));
	return (0);
}

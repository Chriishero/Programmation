/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_non_printable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvillene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:27:11 by cvillene          #+#    #+#             */
/*   Updated: 2025/07/22 12:02:56 by cvillene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ascii_to_hexadecimal(char c)
{
	char	hex[3];
	char	*base16;

	base16 = "0123456789abcdef";
	hex[0] = base16[c / 16];
	hex[1] = base16[c % 16];
	write(1, "\\", 1);
	write(1, hex, 2);
}

void	ft_putstr_non_printable(char *str)
{
	while (*str)
	{
		if ((unsigned char)*str < 32 || (unsigned char)*str == 127)
			ascii_to_hexadecimal((unsigned char)*str);
		else
			write(1, str, 1);
		str++;
	}
}
/*
int main(void)
{
	char str[] = "Hello world \t !";
	ft_putstr_non_printable(str);
	
	return 0;
}*/

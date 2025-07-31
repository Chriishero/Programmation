/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvillene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 08:41:41 by cvillene          #+#    #+#             */
/*   Updated: 2025/07/22 11:46:07 by cvillene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	conditions_char(char *str, int *new_word)
{
	if (*str >= 'a' && *str <= 'z')
	{
		if (*new_word)
		{
			*str -= 32;
		}
		*new_word = 0;
	}
	else if (*str < '0' || *str > '9')
	{
		*new_word = 1;
	}
	else
	{
		*new_word = 0;
	}
}

char	*ft_strcapitalize(char *str)
{
	int	new_word;
	int	i;

	new_word = 1;
	i = 0;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
		i++;
	}
	i = 0;
	while (str[i])
	{
		conditions_char(&str[i++], &new_word);
	}
	return (str);
}
/*
#include <stdio.h>

int main(void)
{
	char str[] = "hi, HOw are you? 42words forty-two; fifty+and+one";
	printf("%s", ft_strcapitalize(str));
	return 0;
}*/

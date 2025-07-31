/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvillene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 08:33:17 by cvillene          #+#    #+#             */
/*   Updated: 2025/07/29 15:22:17 by cvillene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	if (!to_find)
		return (str);
	i = 0;
	while (str[i])
	{
		j = 0;
		while (to_find[j])
		{
			if (str[i + j] != to_find[j])
				break ;
			j++;
		}
		if (!to_find[j])
			return (&str[i]);
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
int main(void)
{
	printf("%s\n", ft_strstr("bonjoiur", "op"));
	printf("%s", strstr("bonjour", "op"));
	return 0;
}*/

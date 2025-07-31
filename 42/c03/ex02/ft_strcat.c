/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvillene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 08:10:47 by cvillene          #+#    #+#             */
/*   Updated: 2025/07/14 11:10:18 by cvillene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>*/

int	ft_strlen(char *dest)
{
	int	i;

	i = 0;
	while (*dest)
	{
		dest++;
		i++;
	}
	return (i);
}

char	*ft_strcat(char *dest, char *src)
{
	char	*dest_temp;
	int		dest_len;
	int		i;

	dest_temp = dest;
	dest_len = ft_strlen(dest_temp);
	i = 0;
	while (src[i])
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest);
}
/*
int main(void)
{
	char src[] = "yuiop";
	char dest[10] = "qwert";
	printf("%s", ft_strcat(dest, src));
	return 0;
}*/

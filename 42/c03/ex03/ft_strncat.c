/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvillene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 08:26:17 by cvillene          #+#    #+#             */
/*   Updated: 2025/07/18 07:31:46 by cvillene         ###   ########.fr       */
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

char	*ft_strncat(char *dest, char *src, unsigned int nb)
{
	char	*dest_temp;
	int		i;
	int		dest_len;

	dest_temp = dest;
	dest_len = ft_strlen(dest_temp);
	i = 0;
	while (src[i] && (unsigned int)i < nb)
	{
		dest[dest_len + (unsigned int)i] = src[i];
		i++;
	}
	dest[dest_len + (unsigned int)i] = '\0';
	return (dest);
}
/*
int main(void)
{
	char src[] = "yuiop";
	char dest[10] = "qwert";
	printf("%s", ft_strcat(dest, src, 3));
	return 0;
}*/

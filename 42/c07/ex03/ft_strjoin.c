/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvillene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 08:59:03 by cvillene          #+#    #+#             */
/*   Updated: 2025/07/26 08:23:11 by cvillene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strsize(char **strs, char *sep, int size)
{
	int	i;
	int	total;

	total = 0;
	i = 0;
	while (i < size && strs[i])
	{
		total += ft_strlen(strs[i]);
		if (i < size - 1)
			total += ft_strlen(sep);
		i++;
	}
	return (total + 1);
}

char	*ft_strjoin(int size, char **strs, char *sep)
{
	int		i;
	char	*str;
	char	*ptr;
	char	*ptrsep;

	if (size <= 0)
		return ("");
	str = (char *)malloc(sizeof(char) * ft_strsize(strs, sep, size));
	if (!str)
		return (NULL);
	ptr = str;
	i = 0;
	while (i < size && *strs)
	{
		while (**strs)
			*ptr++ = *(*strs)++;
		strs++;
		ptrsep = sep;
		while (*ptrsep && i < size - 1 && *strs)
			*ptr++ = *ptrsep++;
		i++;
	}
	*ptr = '\0';
	return (str);
}
/*
#include <stdio.h>

int	main(void)
{
	char *strs[] = {"oui", "AAAHHHH", "memcpy", "ya"};
	printf("%s", ft_strjoin(5, strs, ":non:"));
	return (0);
}*/

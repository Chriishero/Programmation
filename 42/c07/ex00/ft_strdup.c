/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvillene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 08:00:36 by cvillene          #+#    #+#             */
/*   Updated: 2025/07/23 16:30:49 by cvillene         ###   ########.fr       */
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

char	*ft_strdup(char *src)
{
	int		i;
	char	*duplicate;

	duplicate = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!duplicate)
		return (NULL);
	i = 0;
	while (src[i])
	{
		duplicate[i] = src[i];
		i++;
	}
	duplicate[i] = '\0';
	return (duplicate);
}
/*
#include <stdio.h>
int	main(int argc, char *argv[])
{
	if (argc > 1)
	{
		char *dup = ft_strdup(argv[1]);
		printf("%s", dup);
		free(dup);
	}
	return (0);
}*/

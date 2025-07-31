/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvillene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 10:49:34 by cvillene          #+#    #+#             */
/*   Updated: 2025/07/27 07:43:52 by cvillene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_findchar(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_count_words(char *str, char *charset)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && ft_findchar(str[i], charset))
			i++;
		if (str[i])
			count++;
		while (str[i] && !ft_findchar(str[i], charset))
			i++;
	}
	return (count);
}

char	*ft_findword(char *str, char *charset, int *i)
{
	char	*s;
	int		size;
	int		j;

	size = *i;
	while (!ft_findchar(str[size], charset) && str[size])
		size++;
	s = (char *)malloc(sizeof(char) * (size - *i) + 1);
	if (!s)
		return (NULL);
	j = 0;
	while (*i < size)
	{
		s[j++] = str[*i];
		(*i)++;
	}
	s[j] = '\0';
	return (s);
}

char	**ft_split(char *str, char *charset)
{
	int		i;
	int		j;
	char	**tab;

	tab = (char **)malloc(sizeof(char *) * ft_count_words(str, charset) + 1);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (!ft_findchar(str[i], charset))
		{
			tab[j] = ft_findword(str, charset, &i);
			if (!tab[j])
				return (NULL);
			j++;
		}
		else
			i++;
	}
	tab[j] = NULL;
	return (tab);
}
/*
#include <stdio.h>
int	main(int argc, char **argv)
{
	if (argc > 2)
	{
		char **tab = ft_split(argv[1], argv[2]);
		for (int i = 0; tab[i]; i++)
			printf("%s\n", tab[i]);
	}
	return (0);
}*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvillene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 09:48:32 by cvillene          #+#    #+#             */
/*   Updated: 2025/07/30 19:18:30 by cvillene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_readfile(char *path)
{
	int		nbytes;
	char	*buffer;
	int		bytes;
	int		fd;

	buffer = NULL;
	nbytes = 1024;
	bytes = nbytes;
	while (bytes == nbytes)
	{
		fd = open(path, O_RDONLY);
		free(buffer);
		buffer = (char *)malloc(sizeof(char) * nbytes);
		bytes = read(fd, buffer, nbytes);
		close(fd);
		nbytes += 1024;
		bytes += 1024;
	}
	if (bytes == -1)
		ft_puterr("map error\n");
	return (buffer);
}

char	*ft_getmap(char *path)
{
	char	*map;

	map = ft_readfile(path);
	if (ft_is_map_valid(map) == -1)
		return ("map error\n");
	while (*map != '\n')
		map++;
	return (++map);
}

char	**ft_getmatrix(char *map, int row, int col)
{
	char	**matrix;
	int		i;

	matrix = (char **)malloc(sizeof(char *) * row);
	i = 0;
	while (i < row)
	{
		matrix[i] = (char *)malloc(sizeof(char) * sizeof * col + 1);
		i++;
	}
	i = 0;
	while (map[i])
	{
		matrix[i / row][i % col] = map[i];
		i++;
	}
	i = 0;
	while (i < row)
	{
		matrix[i][col] = '\0';
		i++;
	}
	return (matrix);
}

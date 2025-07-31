/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tail.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvillene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:18:44 by cvillene          #+#    #+#             */
/*   Updated: 2025/07/30 09:15:21 by cvillene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_nbytes_to_read(char **argv, int *to_skip)
{
	int	i;
	int	nbytes;
	
	*to_skip = -1;
	nbytes = -1;
	i = 0;
	while (argv[i])
	{
		if (ft_strcmp(argv[i], "-c") == 0)
		{
			*to_skip = i;
			nbytes = ft_atoi(argv[i+1]);
			if (nbytes == -1)
				return (-2);
			return (nbytes);
		}
		i++;
	}
	return (nbytes);
}

char	*ft_cutfilename(char *path)
{
	int	i;
	int	start;
	
	start = 0;
	i = 0;
	while (path[i])
	{
		if (path[i] == '/' || path[i] == '\\')
			start = i + 1;
		i++;
	}
	return (&path[start]);
}

char	*ft_readlastline(int fd, int *bytes)
{
	int		nbytes;
	int		line_count;
	int		start;
	char	*buffer;

	nbytes = 1024;
	buffer = (char *)malloc(sizeof(char) * nbytes);
	*bytes = read(fd, buffer, nbytes);
	while (*bytes > 0)
	{	
		nbytes += 1024;
		free(buffer);
		buffer = (char *)malloc(sizeof(char) * nbytes);
		*bytes = read(fd, buffer, nbytes);
	}
	start = ft_strlen(buffer) - 1;
	line_count = 0;
	while (line_count <= 10)
	{
		if (buffer[start] == '\n')
			line_count++;
		start--;
	}
	return (&buffer[start + 2]);
}

void	ft_show_file(int nbytes, char *path)
{
	int	fd;
	int	bytes;
	char	*buffer;
	
	fd = open(path, O_RDONLY, 0777);
	if (fd == -1)
	{
		ft_puterror(basename(path), strerror(errno), 0);
		return ;
	}
	if (nbytes == -1)
		buffer = ft_readlastline(fd, &bytes);
	else
	{
		buffer = (char *)malloc(sizeof(char) * nbytes + 1);
		bytes = read(fd, buffer, nbytes);
	}
	if (bytes == -1)
	{
		ft_puterror(basename(path), strerror(errno), 0);
		return ;
	}
	close(fd);
	ft_putstr(buffer);
}

void	ft_tail(char **paths)
{
	int	nbytes;
	int	i;
	int	header;
	int	to_skip;
	
	i = 1;
	nbytes = ft_nbytes_to_read(paths, &to_skip);
	if (nbytes == -2)
		return ;
	header = 0;
	if (ft_tabstrlen(&paths[i]) > 1)
		header = 1;
	while (paths[i])
	{
		if (i == to_skip || i == to_skip + 1)
		{
			i++;
			continue ;
		}
		if (header)
			if (ft_putheaderfile(paths[i], i) == -1)
				return ;
		ft_show_file(nbytes, paths[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	if (argc > 1)
		ft_tail(argv);
	return (0);
}

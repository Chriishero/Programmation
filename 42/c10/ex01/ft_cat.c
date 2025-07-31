/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvillene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 09:31:39 by cvillene          #+#    #+#             */
/*   Updated: 2025/07/28 14:23:58 by cvillene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <libgen.h>

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

void	ft_puterror(char *basename, char *err)
{
	ft_putstr("cat: ");
	ft_putstr(basename);
	ft_putstr(": ");
	ft_putstr(err);
	ft_putstr("\n");
}

void	ft_display_file(char *path)
{
	int		fd;
	int		bytes;
	char	buffer[29000];

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_puterror(basename(path), strerror(errno));
		return ;
	}
	bytes = read(fd, buffer, sizeof(buffer));
	while (bytes > 0)
	{
		buffer[bytes] = '\0';
		ft_putstr(buffer);
		bytes = read(fd, buffer, sizeof(buffer));
	}
	if (bytes == -1)
		return ;
	close(fd);
}

void	ft_cat(char **paths)
{
	while (*++paths)
		ft_display_file(*paths);
}

int	main(int argc, char **argv)
{
	if (argc > 1)
		ft_cat(argv);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvillene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 08:02:20 by cvillene          #+#    #+#             */
/*   Updated: 2025/07/28 13:59:44 by cvillene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

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

void	ft_display_file(char *path)
{
	int		fd;
	int		bytes;
	int		bsize;
	char	buffer[1024];

	fd = open(path, O_RDWR, 0777);
	if (fd == -1)
		return ;
	bsize = 1024;
	bytes = read(fd, buffer, size);
	while (bytes > 0)
	{
		buffer[bytes] = '\0';
		ft_putstr(buffer);
		bytes = read(fd, buffer, size);
	}
	if (bytes == -1)
		ft_putstr("Cannot read file.");
	close(fd);
}

int	main(int argc, char **argv)
{
	if (argc == 1)
		ft_putstr("File name missing.");
	else if (argc > 2)
		ft_putstr("Too many arguments.");
	else
		ft_display_file(argv[1]);
	return (0);
}

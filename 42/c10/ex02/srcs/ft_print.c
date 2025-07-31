/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvillene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:02:18 by cvillene          #+#    #+#             */
/*   Updated: 2025/07/30 09:18:19 by cvillene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_puterror(char *basename, char *err, int errtype)
{
	if (errtype == 0)
	{
		ft_putstr("tail: cannot open '");
		ft_putstr(basename);
		ft_putstr("' for reading: ");
		ft_putstr(err);
	}
	else if (errtype == 2)
	{
		ft_putstr("tail: invalid number of bytes: ‘");
		ft_putstr(err);
		ft_putstr("’");
	}
	ft_putstr("\n");
}

int	ft_putheaderfile(char *path, int i_file)
{
	int	fd;

	fd = open(path, O_RDONLY, 0777);
	if (fd == -1)
	{
		ft_puterror(basename(path), strerror(errno), 0);
		return (-1);
	}
	if (i_file > 1)
		ft_putstr("\n");
	ft_putstr("==> ");
	ft_putstr(ft_cutfilename(path));
	ft_putstr(" <==\n");
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvillene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:58:23 by cvillene          #+#    #+#             */
/*   Updated: 2025/07/30 09:16:24 by cvillene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <libgen.h>
# include <stdlib.h>
# include <stdio.h>

void	ft_putstr(char *str);
void	ft_puterror(char *basename, char *err, int errtype);
int		ft_strcmp(char *s1, char *s2);
int		ft_atoi(char *nbr);
int		ft_tabstrlen(char **tab);
int		ft_strlen(char *str);
int	ft_nbytes_to_read(char **argv, int *to_skip);
char	*ft_cutfilename(char *path);
int		ft_putheaderfile(char *path, int i_file);
void	ft_show_file(int nbytes, char *path);
void	ft_tail(char **paths);

#endif

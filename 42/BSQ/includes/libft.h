/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvillene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:03:10 by cvillene          #+#    #+#             */
/*   Updated: 2025/07/30 19:17:14 by cvillene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

void	ft_putstr(char *str);
int		ft_strnchar(char *str, int len, char to_find, int index);
int		ft_atoi(char *str);
char	*ft_readfile(char *path);
char	*ft_getmap(char *path);
char	**ft_getmatrix(char *map);
char	*ft_puterr(char *str);
int		ft_is_firstline_valid(char *map);
int		ft_is_len_valid(char *map);
int		ft_map_has_box(char *map);
int		ft_is_characters_valid(char *map);
int		ft_is_map_valid(char *map);
int		ft_count_rows(char *map);
int		ft_count_columns(char *map);
char	*ft_get_solution(char* map);

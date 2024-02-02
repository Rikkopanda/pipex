/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_timeout.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 18:20:03 by rverhoev          #+#    #+#             */
/*   Updated: 2024/01/04 16:02:21 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_reading_timeout(int fd, char *next_line,
			char **tmp_str)
{
	get_next_line(fd, 1);
	free(next_line);
	next_line = 0;
	free(*tmp_str);
	tmp_str = 0;
}

int	read_loop_timeout(int fd, char	**tmp_str, char	**totalbuf, long i)
{
	char	*next_line;

	i = 0;
	while (i < 200)
	{
		next_line = get_next_line(fd, 0);
		if (next_line == NULL)
			break ;
		*tmp_str = ft_realloc(*tmp_str, ft_strlen(*totalbuf) + 1);
		if (!*tmp_str)
			return (try_free(*tmp_str, *totalbuf, next_line), -1);
		ft_strcpy(*tmp_str, *totalbuf);
		*totalbuf = ft_realloc(*totalbuf, ft_strlen(*totalbuf)
				+ ft_strlen(next_line) + 1);
		if (!(*totalbuf))
			return (try_free(*tmp_str, *totalbuf, next_line), -1);
		ft_strcat(*totalbuf, next_line);
		free(next_line);
		next_line = 0;
		i++;
	}
	free_reading_timeout(fd, next_line, tmp_str);
	return (0);
}

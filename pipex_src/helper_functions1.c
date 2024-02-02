/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 12:33:44 by rik               #+#    #+#             */
/*   Updated: 2024/01/05 15:07:09 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	try_free(char *tmp_str, char *totalbuf, char *nextline)
{
	if (tmp_str)
	{
		free(tmp_str);
		tmp_str = 0;
	}
	if (totalbuf)
	{
		free(totalbuf);
		totalbuf = 0;
	}
	if (nextline)
	{
		free(nextline);
		nextline = 0;
	}
}

void	heredoc_delim_found(char	**tmp_str, char	*next_line)
{
	free(next_line);
	next_line = 0;
	free(*tmp_str);
	*tmp_str = 0;
}

int	eof_condition(char	*next_line, char *delim)
{
	char	*delim_newline;

	if (ft_strnstr(next_line, delim, ft_strlen(next_line)) == next_line
		&& ft_strlen(next_line) == ft_strlen(delim))
		return (1);
	delim_newline = malloc(sizeof(char) * ft_strlen(delim) + 2);
	ft_strcpy(delim_newline, delim);
	ft_strcat(delim_newline, "\n");
	if (ft_strnstr(next_line, delim_newline, ft_strlen(next_line)) == next_line
		&& ft_strlen(next_line) == ft_strlen(delim_newline))
		return (free(delim_newline), 1);
	return (free(delim_newline), 0);
}

void	ft_write_error(char *function, char *path)
{
	char	*print_str;
	int		size;

	size = ft_strlen(function) + ft_strlen(path)
		+ ft_strlen(strerror(errno)) + 10;
	print_str = ft_calloc(sizeof(char), size);
	ft_strcpy(print_str, function);
	ft_strcat(print_str, ": ");
	ft_strcat(print_str, path);
	ft_strcat(print_str, ": ");
	ft_strcat(print_str, strerror(errno));
	ft_strcat(print_str, "\n");
	write(2, print_str, size);
	free(print_str);
}

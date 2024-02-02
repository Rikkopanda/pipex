/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rik <rik@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:35:21 by rverhoev          #+#    #+#             */
/*   Updated: 2024/01/05 11:21:17 by rik              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	read_loop_heredoc(int fd, char	**tmp_str, char	**totalbuf, char *delim)
{
	char	*next_line;

	while (1)
	{
		next_line = get_next_line(fd, 0);
		if (next_line == NULL)
			break ;
		*tmp_str = ft_realloc(*tmp_str, ft_strlen(*totalbuf) + 1);
		if (!*tmp_str)
			return (try_free(*tmp_str, *totalbuf, next_line), -1);
		ft_strcpy(*tmp_str, *totalbuf);
		if (eof_condition(next_line, delim))
			return (try_free(*tmp_str, NULL, next_line), 0);
		*totalbuf = ft_realloc(*totalbuf, ft_strlen(*totalbuf)
				+ ft_strlen(next_line) + 1);
		if (!(*totalbuf))
			return (try_free(*tmp_str, *totalbuf, next_line), -1);
		ft_strcat(*totalbuf, next_line);
		free(next_line);
		next_line = 0;
	}
	return (free(*tmp_str), 0);
}

int	read_loop(int fd, char	**tmp_str, char	**totalbuf)
{
	char	*next_line;

	while (1)
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
	}
	get_next_line(fd, 1);
	free(*tmp_str);
	return (0);
}

int	choose_read_loop(int fd, char **tmp_str, char **totalbuf, t_data *data)
{
	if ((*data).heredoc_bool)
	{
		if (read_loop_heredoc(fd, tmp_str, totalbuf,
				(*data).args.delimiter) == -1)
			return (-1);
	}
	else
	{
		if (ft_strcmp((*data).args.argssplit[0][0], "/dev/urandom") == 0
			|| ft_strcmp((*data).args.argssplit[0][0], "/dev/random") == 0)
		{
			if (read_loop_timeout(fd, tmp_str, totalbuf, 0) == -1)
				return (-1);
		}
		else if (read_loop(fd, tmp_str, totalbuf) == -1)
			return (-1);
	}
	return (0);
}

char	*read_fd(int fd, t_data *data)
{
	char	*totalbuf;
	char	*tmp_str;

	totalbuf = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!totalbuf)
		return (NULL);
	tmp_str = malloc(1);
	if (!totalbuf)
		return (free(totalbuf), NULL);
	tmp_str[0] = '\0';
	totalbuf[0] = '\0';
	if (!(*data).receive_read_bool)
	{
		if (choose_read_loop(fd, &tmp_str, &totalbuf, data) == -1)
			return (free(totalbuf), NULL);
	}
	else
		if (read_loop(fd, &tmp_str, &totalbuf) == -1)
			return (free(totalbuf), NULL);
	return (totalbuf);
}

char	*read_file(char *path, int fd, t_data *data, t_args *args)
{
	char	*str;

	str = NULL;
	if (fd < 0)
	{
		if ((*data).heredoc_bool)
		{
			(*data).args.delimiter = *(*args).argssplit[1];
			str = read_fd(0, data);
		}
		else
		{
			if (access(path, F_OK | R_OK) == -1)
				return (ft_write_error("access", path), NULL);
			fd = open(path, O_RDONLY);
			if (fd < 0)
				return (ft_write_error("open", path), NULL);
			str = read_fd(fd, data);
			close(fd);
		}
	}
	else
		str = read_fd(fd, data);
	return (str);
}

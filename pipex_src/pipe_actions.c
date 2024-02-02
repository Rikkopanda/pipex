/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:35:27 by rverhoev          #+#    #+#             */
/*   Updated: 2024/01/05 15:05:52 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	write_from_parent_to_cmd(int pipe_send_to_cmd[2],
		int pipe_send_back[2], char *buf, t_data *data)
{
	close(pipe_send_to_cmd[READ]);
	if (buf)
		write(pipe_send_to_cmd[WRITE], buf, strlen(buf));
	close(pipe_send_to_cmd[WRITE]);
	close(pipe_send_back[WRITE]);
	free(buf);
	(*data).buf_freed_bool = 1;
	buf = 0;
}

void	wait_children(t_data *data)
{
	int	j;

	j = 0;
	while (j < (*data).nbr_of_forks - 1)
	{
		wait(&(*data).status);
		j++;
	}
}

void	receive(int sent_pipe[2], int receive_pipe[2], t_data *data, int *i)
{
	wait_children(data);
	(*data).receive_read_bool = 1;
	if (*i != 1 + (*data).heredoc_bool)
	{
		if (*i != 2 + (*data).heredoc_bool)
		{
			close(sent_pipe[WRITE]);
			close(sent_pipe[READ]);
		}
		close(receive_pipe[WRITE]);
	}
	(*data).buf = read_file(NULL, receive_pipe[READ], data, NULL);
	close(receive_pipe[READ]);
	wait(&(*data).status);
}

void	close_pipes(int *pipe, int increment)
{
	int	i;

	i = 0;
	while (i <= increment)
	{
		close(pipe[WRITE]);
		close(pipe[READ]);
		pipe = pipe - 1;
		i++;
	}
}

void	write_out_pluscleanup(t_data *data, char *buf, int outfile_i)
{
	int	fd;

	if (check_access(data, buf, outfile_i))
		return ;
	if ((*data).heredoc_bool)
		fd = open((*data).args.argssplit[outfile_i][0],
				O_WRONLY | O_CREAT | O_APPEND, 0664);
	else
		fd = open((*data).args.argssplit[outfile_i][0],
				O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd < 0)
		(*data).status = 1;
	else
		(*data).status = 0;
	write(fd, buf, ft_strlen(buf));
	close(fd);
	free_pipe_array(data, (*data).nbr_of_cmds + 1);
	free(buf);
	free_args(&(*data).args);
}

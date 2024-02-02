/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:06:55 by rverhoev          #+#    #+#             */
/*   Updated: 2024/01/05 15:10:18 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_access(t_data *data, char *buf, int outfile_i)
{
	if (access((*data).args.argssplit[outfile_i][0], F_OK) == 0)
	{
		if (access((*data).args.argssplit[outfile_i][0], W_OK) == -1)
		{
			ft_write_error("access", (*data).args.argssplit[outfile_i][0]);
			free(buf);
			free_args(&(*data).args);
			(*data).status = 1;
			return (1);
		}
	}
	return (0);
}

void	set_data(int nbr_of_cmds, char **envp, t_data *data)
{
	(*data).nbr_of_forks = 0;
	(*data).nbr_of_cmds = nbr_of_cmds;
	(*data).envp = envp;
	(*data).heredoc_bool = 0;
	(*data).receive_read_bool = 0;
	(*data).status = 0;
	(*data).buf_freed_bool = 0;
}

void	free_pipe_array(t_data *data, int j)
{
	while (j >= 0)
	{
		free((*data).pipe_array[j]);
		(*data).pipe_array[j] = 0;
		j--;
	}
	free((*data).pipe_array);
	(*data).pipe_array = 0;
}

int	alloc_pipe_array(t_data *data)
{
	int	j;

	j = 0;
	(*data).pipe_array = malloc(sizeof(int *) * ((*data).nbr_of_cmds + 2));
	if (!(*data).pipe_array)
		return (-1);
	while (j < (*data).nbr_of_cmds + 2)
	{
		(*data).pipe_array[j] = (int *)malloc(sizeof(int) * 2);
		if (!(*data).pipe_array[j])
			return (free_pipe_array(data, j), -1);
		j++;
	}
	return (0);
}

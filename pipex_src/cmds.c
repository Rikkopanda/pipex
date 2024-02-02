/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:35:31 by rverhoev          #+#    #+#             */
/*   Updated: 2024/01/05 15:08:30 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	after_execve_fails(char	**cmd_arg, t_data *data)
{
	int		bytes_read;
	char	error_case_buf[10];

	bytes_read = 1;
	ft_write_error("execve", cmd_arg[0]);
	while (bytes_read > 0)
		bytes_read = read(STDIN_FILENO, error_case_buf, 10);
	write(STDOUT_FILENO, "", 0);
	if (!data->buf_freed_bool)
	{
		free(data->buf);
		data->buf = 0;
	}
	free_pipe_array(data, (*data).nbr_of_cmds + 1);
	free_args(&data->args);
}

void	cmd(int *pipe_send_to_cmd, int *pipe_send_back, int i, t_data *data)
{
	char	*path;
	char	**cmd_arg;

	cmd_arg = (*data).args.argssplit[i];
	path = malloc(sizeof(char) * (ft_strlen(cmd_arg[0])
				+ ft_strlen("/bin/") + 1));
	dup2(pipe_send_to_cmd[READ], STDIN_FILENO);
	close(pipe_send_to_cmd[READ]);
	if (i + (*data).heredoc_bool != 2)
		close(pipe_send_to_cmd[WRITE]);
	close(pipe_send_back[READ]);
	dup2(pipe_send_back[WRITE], STDOUT_FILENO);
	close(pipe_send_back[WRITE]);
	ft_strcpy(path, "/bin/");
	execve(ft_strcat(path, cmd_arg[0]), cmd_arg, (*data).envp);
	free(path);
	after_execve_fails(cmd_arg, data);
	exit(EXIT_FAILURE);
}

// if(i == (*ptrs).nbr_of_cmds)
// {
// 	dup2_stdout_to_file();
// dup2(argv[nbr_of_cmds], STDOUT_FILENO);
// }
// else
// STDIN STILL POINTS TO pipe_send_to_cmd[0]
// STDOUT STILL POINTS TO pipe_send_back[1]
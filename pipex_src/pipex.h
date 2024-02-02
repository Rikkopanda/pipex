/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 15:04:24 by rverhoev          #+#    #+#             */
/*   Updated: 2024/01/05 15:08:12 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h> 
# include "../pip_lib/pip_lib.h"
# include "../gnl/get_next_line.h"
# include <sys/wait.h>
# include "errno.h"

# define WRITE 1
# define READ 0

typedef struct s_args
{
	char	***argssplit;
	char	*delimiter;
}	t_args;

typedef struct s_data
{
	int		status;
	int		receive_read_bool;
	int		buf_freed_bool;
	int		heredoc_bool;
	int		nbr_of_cmds;
	int		nbr_of_forks;
	int		**pipe_array;
	char	*buf;
	t_args	args;
	char	**envp;
}	t_data;

// args_parsing
int		parse_args(t_args *args, char **argv, int argc, t_data *data);
void	free_args(t_args *args);

// file reading
char	*read_fd(int fd, t_data *data);
char	*read_file(char *path, int fd, t_data *data, t_args *args);
void	try_free(char *tmp_str, char *totalbuf, char *nextline);
int		eof_condition(char	*next_line, char *delim);
void	heredoc_delim_found(char	**tmp_str, char	*next_line);
int		read_loop_timeout(int fd, char	**tmp_str, char	**totalbuf, long i);

// cmd
void	cmd(int *pipe_send_to_cmd, int *pipe_send_back, int i, t_data *ptrs);

// pipe_actions
void	write_from_parent_to_cmd(int pipe_send_to_cmd[2], int pipe_send_back[2],
			char *buf, t_data *data);
void	receive(int sent_pipe[2], int receive_pipe[2], t_data *data, int *i);
void	write_out_pluscleanup(t_data *data, char *buf, int outfile_i);
void	close_pipes(int *pipe, int increment);

// helper functions 1
void	ft_write_error(char *function, char *path);
void	set_data(int nbr_of_cmds, char **envp, t_data *data);
void	free_pipe_array(t_data *data, int j);
void	wait_children(t_data *data);
int		check_access(t_data *data, char *buf, int outfile_i);

// helper functions 2
void	set_data(int nbr_of_cmds, char **envp, t_data *data);
void	free_pipe_array(t_data *data, int j);
int		alloc_pipe_array(t_data *data);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rik <rik@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:35:34 by rverhoev          #+#    #+#             */
/*   Updated: 2024/01/05 11:32:03 by rik              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	parse_args(t_args *args, char **argv, int argc, t_data *data)
{
	int	i;

	(*args).argssplit = malloc(sizeof(char **) * argc);
	if (!(*args).argssplit)
		return (-1);
	i = 1;
	while (i < argc)
	{
		(*args).argssplit[i - 1] = ft_split(argv[i], ' ');
		if (!(*args).argssplit[i - 1])
			return (-1);
		i++;
	}
	if (ft_strcmp((const char *)(*args).argssplit[0][0], "heredoc") == 0)
		(*data).heredoc_bool = 1;
	(*args).argssplit[i - 1] = NULL;
	return (0);
}

void	free_args(t_args *args)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if ((*args).argssplit == NULL)
		return ;
	while ((*args).argssplit[i] != NULL)
	{
		while ((*args).argssplit[i][j] != NULL)
		{
			free((*args).argssplit[i][j]);
			j++;
		}
		free((*args).argssplit[i][j]);
		j = 0;
		free((*args).argssplit[i]);
		i++;
	}
	if ((*args).argssplit[i] == NULL)
		return (free((*args).argssplit));
	free((*args).argssplit[i]);
	free((*args).argssplit);
}

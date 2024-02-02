/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:17:33 by rverhoev          #+#    #+#             */
/*   Updated: 2023/10/31 10:17:36 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include "stdlib.h"
# include "../pip_lib/pip_lib.h"
# include "stdio.h"
# include "unistd.h"

typedef struct s_gnl_list
{
	char				*buffer;
	struct s_gnl_list	*next;
}	t_gnl_list;

char		*get_next_line(int fd, int free_all);
char		*create_list(int fd, t_gnl_list **list);
char		*make_next_line(t_gnl_list **list, int size);
void		create_leftover(t_gnl_list **list, char *left_over_str);
char		*ret_next_line(t_gnl_list **list);
char		*ps_strchr(const char *s, int c);
t_gnl_list	*ps_lstnew_strdup(void *buffer);
void		ps_lstclear(t_gnl_list **lst);
t_gnl_list	*lstlast0_lstback1(t_gnl_list **lst, t_gnl_list *new,
				int last0_back1);
int			find_newline(t_gnl_list *node);

#endif

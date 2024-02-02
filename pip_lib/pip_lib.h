/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:11:45 by rverhoev          #+#    #+#             */
/*   Updated: 2023/10/15 13:11:50 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIP_LIB_H
# define PIP_LIB_H

# include <stdlib.h>
# include <stddef.h>
# include <stdio.h>
# include <unistd.h>

void	*ft_realloc(void *ptr, size_t size);
void	*ft_calloc(size_t nmemb, size_t size);
size_t	ft_strlen(const char *s);
void	ft_strcpy(char *dest, const char *src);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strdup(const char *s);
char	**ft_split(const char *s, char c);
int		ft_atoi(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcat(char *dest, char *src);
char	*strnstr(const char *big,	const char *little, size_t len);
char	*ft_strnstr(const char *big,	const char *little, size_t len);
void	ft_bzero(void *s, size_t n);
char	*ft_strchr(const char *s, int c);

#endif
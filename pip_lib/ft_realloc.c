/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:01:33 by rverhoev          #+#    #+#             */
/*   Updated: 2024/01/04 16:00:39 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pip_lib.h"

void	*ft_realloc(void *ptr, size_t size)
{
	char	*new_ptr;

	if (!size && ptr)
	{
		free(ptr);
		ptr = 0;
		return (NULL);
	}
	else if (!size)
		return (NULL);
	new_ptr = malloc(size);
	if (!new_ptr)
		return (NULL);
	new_ptr[0] = '\0';
	ft_strlcpy(new_ptr, ptr, size);
	free(ptr);
	ptr = 0;
	return ((void *)new_ptr);
}

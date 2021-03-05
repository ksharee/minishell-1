/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleonel <pleonel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 16:18:32 by ksharee           #+#    #+#             */
/*   Updated: 2021/03/01 19:31:53 by pleonel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	*ptr;
	size_t	size_all;

	size_all = count * size;
	ptr = (size_t *)malloc(size_all);
	if (!(ptr))
		return (NULL);
	ft_memset(ptr, 0, size_all);
	return (ptr);
}

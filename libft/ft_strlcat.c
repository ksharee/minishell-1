/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleonel <pleonel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:50:06 by ksharee           #+#    #+#             */
/*   Updated: 2021/03/01 19:03:50 by pleonel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	size;

	size = 0;
	while (dst[size] && size < dstsize)
		size++;
	i = size;
	while (src[size - i] && size + 1 < dstsize)
	{
		dst[size] = src[size - i];
		size++;
	}
	if (i < dstsize)
		dst[size] = '\0';
	return (i + ft_strlen(src));
}

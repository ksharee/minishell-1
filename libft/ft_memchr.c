/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharee <ksharee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:44:36 by ksharee           #+#    #+#             */
/*   Updated: 2020/11/02 15:45:26 by ksharee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*a;
	unsigned char	c_new;

	a = (unsigned char *)s;
	c_new = (unsigned char)c;
	i = 0;
	while (n--)
	{
		if (a[i] == c_new)
			return (a + i);
		i++;
	}
	return (NULL);
}

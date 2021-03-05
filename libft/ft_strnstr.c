/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharee <ksharee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:38:43 by ksharee           #+#    #+#             */
/*   Updated: 2020/11/03 14:05:52 by ksharee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	ii;
	char	*a;
	char	*b;

	a = (char *)haystack;
	b = (char *)needle;
	i = 0;
	if (b[0] == '\0')
		return (a);
	while (a[i] && i < len)
	{
		ii = 0;
		if (a[i] == b[ii])
		{
			while (i + ii < len && a[i + ii] == b[ii])
			{
				ii++;
				if (!b[ii])
					return (&a[i]);
			}
		}
		i++;
	}
	return (NULL);
}

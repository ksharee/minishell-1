/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharee <ksharee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 09:38:40 by ksharee           #+#    #+#             */
/*   Updated: 2021/03/05 12:36:01 by ksharee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	size_t	i;
	char	*ptr;

	i = 0;
	size = ft_strlen(s1) + ft_strlen(s2);
	ptr = (char *)malloc(size + 1);
	if (!(ptr))
		return (NULL);
	while (s1 && *s1 != '\0')
	{
		ptr[i] = *s1;
		i++;
		s1++;
	}
	while (s2 && *s2 != '\0')
	{
		ptr[i] = *s2;
		i++;
		s2++;
	}
	ptr[i] = '\0';
	return (ptr);
}

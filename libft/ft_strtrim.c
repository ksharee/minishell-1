/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharee <ksharee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 12:01:20 by ksharee           #+#    #+#             */
/*   Updated: 2021/03/05 16:59:16 by ksharee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_start_str(char *s, char *set)
{
	int		i;
	int		start;
	int		flag;

	i = 0;
	start = 0;
	flag = 0;
	while (s[start])
	{
		while (set[i])
		{
			if (s[start] == set[i])
			{
				flag = 1;
				break ;
			}
			flag = 0;
			i++;
		}
		if (flag == 0)
			break ;
		i = 0;
		start++;
	}
	return (start);
}

static int	ft_end_str(char *s, char *set)
{
	int	i;
	int	end;
	int	flag;

	end = ft_strlen(s);
	i = 0;
	flag = 0;
	while (end)
	{
		while (set[i])
		{
			if (s[end - 1] == set[i])
			{
				flag = 1;
				break ;
			}
			i++;
			flag = 0;
		}
		if (flag == 0)
			break ;
		i = 0;
		end--;
	}
	return (end);
}

static void	ft_set_ptr(char *s, char *ptr, int start, int end)
{
	int	i;
	int	size;

	size = end - start;
	i = 0;
	while (i < size)
	{
		ptr[i] = s[start];
		start++;
		i++;
	}
	ptr[i] = '\0';
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	int		start;
	int		end;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = ft_start_str((char *)s1, (char *)set);
	end = ft_end_str((char *)s1, (char *)set);
	if (end - start < 0)
		return (ft_strdup(""));
	ptr = (char *)malloc(end - start + 1);
	if (!(ptr))
		return (NULL);
	ft_set_ptr((char *)s1, ptr, start, end);
	return (ptr);
}

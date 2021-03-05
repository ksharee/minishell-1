/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goodluck <goodluck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 15:00:51 by pleonel           #+#    #+#             */
/*   Updated: 2021/02/20 23:32:09 by goodluck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strnjoin(char **s1, char const *s2, size_t n_s2)
{
	size_t	len_res_s;
	size_t	i;
	size_t	j;
	char	*res_s;

	if (*s1 == NULL || s2 == NULL)
		return (NULL);
	len_res_s = ft_strlen(*s1) + n_s2 + 1;
	res_s = (char*)malloc(sizeof(char) * len_res_s);
	if (res_s == NULL)
	{
		*s1 = res_s;
		return (NULL);
	}
	i = 0;
	j = 0;
	while ((*s1)[i] != '\0')
		res_s[j++] = (*s1)[i++];
	i = 0;
	while (i < n_s2 && s2[i])
		res_s[j++] = s2[i++];
	res_s[j] = '\0';
	free(*s1);
	*s1 = res_s;
	return (*s1);
}

char	*ft_strdup(const char *s1)
{
	char	*res;
	size_t	len;
	size_t	i;

	len = ft_strlen(s1);
	res = (char*)malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (res);
	i = 0;
	while (i != len)
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	if (s == NULL)
		return (i);
	while (s[i] != '\0')
		i++;
	return (i);
}

int		ft_str_find_char(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	if (s[i] == c)
		return (i);
	else
		return (-1);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res_s;
	size_t	len_s;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	i = ft_strlen(s);
	if (i < start)
		len_s = 0;
	else if (len > i - start)
		len_s = i - start;
	else
		len_s = len;
	res_s = (char*)malloc(sizeof(char) * (len_s + 1));
	if (res_s == NULL)
		return (NULL);
	res_s[len_s] = '\0';
	i = 0;
	while (i < len_s)
		res_s[i++] = s[start++];
	return (res_s);
}

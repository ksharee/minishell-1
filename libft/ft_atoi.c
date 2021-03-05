/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleonel <pleonel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 11:46:20 by ksharee           #+#    #+#             */
/*   Updated: 2021/03/01 18:56:05 by pleonel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long int	i;
	long int	rez;
	int			minus;

	i = 0;
	rez = 0;
	minus = 1;
	while (str[i] && (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || \
			str[i] == '\v' || str[i] == '\f' || str[i] == '\r'))
		i++;
	if (str[i] == '-')
	{
		minus = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= 48 && str[i] <= 57)
		rez = rez * 10 + str[i++] - '0';
	if (i > 25 && minus < 0)
		return (0);
	if (i > 25 && minus > 0)
		return (-1);
	return (rez * minus);
}

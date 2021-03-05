/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharee <ksharee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 09:28:12 by ksharee           #+#    #+#             */
/*   Updated: 2020/11/03 14:54:27 by ksharee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	tmp;
	char		c[32];
	int			i;

	i = 0;
	tmp = (long)n;
	if (tmp < 0)
	{
		write(fd, "-", 1);
		tmp *= -1;
	}
	if (tmp == 0)
		write(fd, "0", 1);
	while (tmp)
	{
		c[i] = (tmp % 10) + '0';
		tmp /= 10;
		i++;
	}
	c[i] = '\0';
	while (i)
	{
		write(fd, &c[i - 1], 1);
		i--;
	}
}

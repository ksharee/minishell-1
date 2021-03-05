/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharee <ksharee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 14:38:12 by ksharee           #+#    #+#             */
/*   Updated: 2021/03/05 16:59:07 by ksharee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size_n(int n)
{
	size_t	size;

	size = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		size++;
	while (n)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char		*ft_itoa(int n)
{
	char	*ptr;
	size_t	size;
	size_t	i;

	i = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	size = ft_size_n(n);
	ptr = (char *)malloc(size + 1);
	if (!(ptr))
		return (NULL);
	if (n < 0)
	{
		ptr[0] = '-';
		n *= -1;
		i++;
	}
	ptr[size] = '\0';
	while (i < size--)
	{
		ptr[size] = (n % 10) + '0';
		n /= 10;
	}
	return (ptr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goodluck <goodluck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 16:50:33 by goodluck          #+#    #+#             */
/*   Updated: 2021/03/02 21:17:50 by goodluck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_n(t_param *all)
{
	int	i;
	int	ii;

	i = 0;
	while (all->line[++i])
	{
		ii = 0;
		while (all->line[i][++ii])
		{
			if (all->line[i][ii] != 'n')
				return (i - 1);
		}
		all->echo_n = 1;
	}
	return (1);
}

int		echo_run(t_param *all)
{
	int i;

	i = 0;
	all->echo_n = 0;
	if (size_arg(all) == 1)
	{
		write(1, "\n", 1);
		return (0);
	}
	if (all->line[1][0] == '-')
		i = check_n(all);
	while (all->line[++i])
	{
		ft_putstr_fd(all->line[i], 1);
		!all->line[i + 1] ? 0 : write(1, " ", 1);
	}
	all->echo_n == 0 ? write(1, "\n", 1) : 0;
	return (0);
}

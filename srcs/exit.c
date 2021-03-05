/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goodluck <goodluck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 10:04:48 by ksharee           #+#    #+#             */
/*   Updated: 2021/03/05 22:17:29 by goodluck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error(t_param *all)
{
	if (is_num_char(all->line[1]) == 1)
	{
		error("exit: ", all->line[1], "numeric argument required");
		exit(255);
	}
	if ((ft_strlen(all->line[1]) == 19 &&
		ft_strncmp(all->line[1], "9223372036854775807", 20) > 0) ||
		(ft_strlen(all->line[1]) == 20 &&
		ft_strncmp(all->line[1], "-9223372036854775808", 21) > 0) ||
		ft_strlen(all->line[1]) > 20)
	{
		error("exit: ", all->line[1], "numeric argument required");
		exit(255);
	}
}

void	exit_run(t_param *all)
{
	int	i;

	if (all->pipe_size > 0)
	{
		g_exit.exit = 0;
		return ;
	}
	ft_putstr_fd("exit", 1);
	write(1, "\n", 1);
	size_arg(all) == 1 ? exit(g_exit.exit) : 0;
	exit_error(all);
	if (size_arg(all) > 2)
	{
		error("exit: ", "", "too many arguments");
		g_exit.exit = 1;
		return ;
	}
	i = ft_atoi(all->line[1]);
	exit(i);
}

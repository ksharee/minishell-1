/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharee <ksharee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 15:49:16 by pleonel           #+#    #+#             */
/*   Updated: 2021/03/04 15:57:07 by ksharee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	processor(t_param *all)
{
	if (all->pipe_flag == 1)
	{
		all->pipe_size++;
		pipe_run(all);
		return ;
	}
	if (!ft_strncmp(all->line[0], "echo", 5))
		g_exit.exit = echo_run(all);
	else if (!ft_strncmp(all->line[0], "pwd", 4))
		g_exit.exit = pwd_run(all);
	else if (!ft_strncmp(all->line[0], "env", 4))
		g_exit.exit = env_run(all);
	else if (!ft_strncmp(all->line[0], "cd", 3))
		g_exit.exit = cd_run(all);
	else if (!ft_strncmp(all->line[0], "export", 7))
		g_exit.exit = export_run(all);
	else if (!ft_strncmp(all->line[0], "unset", 6))
		g_exit.exit = unset_run(all);
	else if (!ft_strncmp(all->line[0], "exit", 5))
		exit_run(all);
	else
		exec_run(all);
	wait_pipe(all);
}

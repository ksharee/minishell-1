/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goodluck <goodluck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 18:22:03 by pleonel           #+#    #+#             */
/*   Updated: 2021/03/06 00:21:42 by goodluck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line.h"

void	ft_free_all_line(t_param *all)
{
	int i;

	i = -1;
	while (all->line[++i])
		free(all->line[i]);
	free(all->line);
}

void	display_msg(void)
{
	ft_putstr_fd("\e[1;33mMiniShell > \e[0m", 1);
}

void	minishell_init(t_param *all, char **envp)
{
	all->fd_0 = dup(0);
	all->fd_1 = dup(1);
	all->pipe_size = 0;
	all->redirect_size = 0;
	all->pipe_flag = 0;
	g_exit.exit = 0;
	all->env_array = NULL;
	all->env_new = env_copy(envp, all);
	shlvl_up(all);
	pwd_clear(all);
	g_exit.mini = 0;
	all->fd_redir = 0;
	display_msg();
}

void	run_command(t_param *all)
{
	g_exit.is_signal = 0;
	if (all->line[0] != NULL)
		processor(all);
	if (all->redirect_size > 0 && all->pipe_flag == 0)
	{
		dup2(all->fd_0, 0);
		dup2(all->fd_1, 1);
		all->redirect_size = 0;
	}
	free_split(all->line);
}

int		main(int agrc, char **agrv, char **envp)
{
	t_param	all;
	int		i;
	char	*line;

	minishell_init(&all, envp);
	while (1)
	{
		signal_init();
		env_to_array(&all);
		get_next_line(0, &line);
		i = 0;
		while ((i = parsing(&all, line, i)))
			run_command(&all);
		run_command(&all);
		display_msg();
		free(line);
	}
	(void)agrc;
	(void)agrv;
}

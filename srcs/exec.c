/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goodluck <goodluck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 23:07:01 by goodluck          #+#    #+#             */
/*   Updated: 2021/03/06 00:29:14 by goodluck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_env_path(t_param *all)
{
	char	*str;
	char	**path_array;
	int		i;

	i = -1;
	if (!(str = env_search("PATH", all)))
	{
		error(all->line[0], "", "No such file or directory");
		exit(COMMAND_NOT_FOUND);
	}
	path_array = ft_split(str, ':');
	while (path_array && path_array[++i])
	{
		str = ft_strjoin_three(path_array[i], "/", all->line[0]);
		execve(str, all->line, all->env_array);
		free(str);
	}
	error(all->line[0], "", "command not found");
	free_split(path_array);
	exit(COMMAND_NOT_FOUND);
}

void	exec_absolut_path(t_param *all)
{
	if (execve(all->line[0], all->line, all->env_array) == -1)
	{
		error(all->line[0], "", strerror(errno));
		if (errno == EACCES)
			exit(PERMISSION_DENIED);
		exit(FAILED);
	}
}

void	exec_run(t_param *all)
{
	pid_t	pid;

	if (pid_init(&pid) == 0)
		return ;
	!ft_strncmp(all->line[0], "./minishell", 11) ? g_exit.mini = 1 : 0;
	if (pid == 0)
	{
		if (!ft_strncmp(all->line[0], "/", 1) ||
			!ft_strncmp(all->line[0], "./", 2) ||
			!ft_strncmp(all->line[0], "../", 3))
			exec_absolut_path(all);
		else
			exec_env_path(all);
	}
	else
	{
		if (signal(SIGQUIT, sig_catcher_exec) == SIG_ERR)
			exit(ERROR_SIGQUIT);
		if (signal(SIGINT, sig_catcher_exec) == SIG_ERR)
			exit(ERROR_SIGINT);
		wait(&pid);
		if (g_exit.is_signal == 0)
			g_exit.exit = WEXITSTATUS(pid);
		!ft_strncmp(all->line[0], "./minishell", 11) ? g_exit.mini = 0 : 0;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharee <ksharee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 14:25:55 by ksharee           #+#    #+#             */
/*   Updated: 2021/03/05 13:08:39 by ksharee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_pipe(t_param *all)
{
	int	status;

	while (all->pipe_size)
	{
		dup2(all->fd_0, 0);
		dup2(all->fd_1, 1);
		wait(&status);
		all->pipe_size--;
	}
}

void	dup_close(int fd[2], int dup_fd)
{
	dup2(fd[dup_fd], dup_fd);
	close(fd[0]);
	close(fd[1]);
}

void	command_search(t_param *all)
{
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
	{
		if (!ft_strncmp(all->line[0], "/", 1) ||
			!ft_strncmp(all->line[0], "./", 2) ||
			!ft_strncmp(all->line[0], "../", 3))
			exec_absolut_path(all);
		else
			exec_env_path(all);
	}
}

void	pipe_run(t_param *all)
{
	pid_t pid;

	if (pipe(all->fd) == -1)
	{
		error("pipe: ", "", strerror(errno));
		g_exit.exit = 1;
		return ;
	}
	if (pid_init(&pid) == 0)
		return ;
	if (pid == 0)
	{
		dup_close(all->fd, 1);
		command_search(all);
		kill(getpid(), SIGKILL);
	}
	else
	{
		dup_close(all->fd, 0);
		g_exit.exit = WEXITSTATUS(pid);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goodluck <goodluck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 11:18:04 by ksharee           #+#    #+#             */
/*   Updated: 2021/03/06 00:20:48 by goodluck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd(t_param *all)
{
	char	pwd[1000];
	char	*str;

	if (getcwd(pwd, 1000) == NULL)
	{
		error("cd: ", "error retrieving current directory: \
			getcwd: cannot access parent directories", strerror(errno));
		env_update(all, "OLDPWD", env_search("PWD", all), 0);
		str = ft_strjoin_three(env_search("OLDPWD", all), "/", all->line[1]);
		env_update(all, "PWD", str, 0);
		free(str);
	}
	else
	{
		env_update(all, "OLDPWD", env_search("PWD", all), 0);
		env_update(all, "PWD", pwd, 0);
	}
	g_exit.exit = 0;
}

void	old_pwd_func(t_param *all)
{
	char	*old_pwd;

	if (!(old_pwd = env_search("OLDPWD", all)))
	{
		error("cd: ", NULL, "OLDPWD not set");
		g_exit.exit = 1;
	}
	else if (chdir(old_pwd) == -1)
	{
		error("cd: ", old_pwd, strerror(errno));
		g_exit.exit = 1;
	}
	else
	{
		update_pwd(all);
		pwd_run(all);
	}
}

void	tilda_func(t_param *all)
{
	char	*tmp;

	if (all->line[1][0] == '~')
	{
		tmp = ft_strjoin(all->tilda, all->line[1] + 1);
		free(all->line[1]);
		all->line[1] = tmp;
	}
	if (chdir(all->line[1]) == -1)
	{
		error("cd: ", all->line[1], strerror(errno));
		g_exit.exit = 1;
	}
	else
		update_pwd(all);
}

int		cd_run(t_param *all)
{
	errno = 0;
	if (size_arg(all) > 2)
	{
		error("cd: ", NULL, "too many arguments");
		return (1);
	}
	if (!all->line[1])
	{
		if ((chdir(env_search("HOME", all)) == -1)
			&& env_search("HOME", all) == NULL)
		{
			error("cd: ", NULL, "HOME not set");
			return (1);
		}
		else
			update_pwd(all);
	}
	else if (!ft_strncmp(all->line[1], "-", 1))
		old_pwd_func(all);
	else
		tilda_func(all);
	return (g_exit.exit);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goodluck <goodluck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 09:51:01 by ksharee           #+#    #+#             */
/*   Updated: 2021/03/05 22:09:51 by goodluck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			check_plus_env(char c, char *str)
{
	free(str);
	if (c != '=')
		return (1);
	else
		return (2);
}

int			check_line(char *str)
{
	char	*not_valid;
	int		i;
	int		ii;

	ii = 0;
	i = 0;
	if ((str[i] >= '1' && str[i] <= '9') || str[i] == '=')
		return (1);
	not_valid = ft_strdup("!@#$%^&*()-{}[]:?±~/");
	while (str[i] && str[i] != '=')
	{
		ii = -1;
		while (not_valid[++ii])
			if (str[i] == not_valid[ii])
			{
				free(not_valid);
				return (1);
			}
		if (str[i] == '+')
			return (check_plus_env(str[i + 1], not_valid));
		i++;
	}
	free(not_valid);
	return (0);
}

static char	*env_search_unset(char *str, t_param *all)
{
	t_envcopy	*tmp;

	tmp = all->env_new;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, str, ft_strlen(str) + 1) && tmp->unset == 0)
			return (tmp->key);
		tmp = tmp->next;
	}
	return (NULL);
}

void		env_unset(t_param *all, char *key)
{
	t_envcopy *tmp;

	tmp = all->env_new;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, ft_strlen(key) + 1))
		{
			tmp->unset = 1;
			break ;
		}
		tmp = tmp->next;
	}
}

int			unset_run(t_param *all)
{
	int	i;

	i = 0;
	if (size_arg(all) == 1)
		return (0);
	while (all->line[++i])
	{
		if (check_line(all->line[i]) == 1)
		{
			error("unset: ", all->line[i], "not a valid identifier");
			continue ;
		}
		if (env_search_unset(all->line[i], all))
			env_unset(all, all->line[i]);
	}
	return (0);
}

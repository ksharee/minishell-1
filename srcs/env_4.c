/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goodluck <goodluck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 13:09:27 by ksharee           #+#    #+#             */
/*   Updated: 2021/03/06 00:25:28 by goodluck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_join(t_param *all, char *str, char *new_str, int unset)
{
	t_envcopy	*tmp;
	char		*value;

	tmp = all->env_new;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, str, ft_strlen(str) + 1))
		{
			tmp->sep = 1;
			if (unset == 1)
			{
				tmp->unset = 0;
				free(tmp->value);
				tmp->value = ft_strdup(new_str);
				return ;
			}
			value = ft_strjoin(tmp->value, new_str);
			free(tmp->value);
			tmp->value = value;
			return ;
		}
		tmp = tmp->next;
	}
}

void	sort_list(t_param *all)
{
	all->flag = true;
	while (all->flag)
	{
		all->flag = false;
		all->ptr = all->env_copy;
		while (all->ptr->next)
		{
			if (ft_strncmp(all->ptr->key, all->ptr->next->key,
				ft_strlen(all->ptr->next->key)) > 0)
			{
				if (all->ptr == all->env_copy)
				{
					swap_envcopy(&all->ptr, &all->env_copy);
					all->flag = true;
				}
				else
				{
					swap_envcopy(&all->ptr, &all->prev->next);
					all->flag = true;
				}
			}
			all->prev = all->ptr;
			all->ptr = all->ptr->next;
		}
	}
}

void	pwd_clear(t_param *all)
{
	char	*str;

	str = env_search("OLDPWD", all);
	if (!str)
		env_add_back(&all->env_new, env_new("OLDPWD", "", 1));
	else
		env_update(all, "OLDPWD", "", 1);
}

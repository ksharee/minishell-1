/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goodluck <goodluck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 21:26:35 by goodluck          #+#    #+#             */
/*   Updated: 2021/03/05 22:07:54 by goodluck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*env_search(char *str, t_param *all)
{
	t_envcopy	*tmp;

	tmp = all->env_new;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, str, ft_strlen(str) + 1) && tmp->unset == 0)
		{
			if (tmp->value == NULL)
				return ("");
			return (tmp->value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char		*env_search_all(char *str, t_param *all)
{
	t_envcopy	*tmp;

	tmp = all->env_new;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, str, ft_strlen(str) + 1))
			return (tmp->key);
		tmp = tmp->next;
	}
	return (NULL);
}

void		env_clear(t_envcopy **lst, void (*del)(void*))
{
	t_envcopy *old_elem;

	if (*lst)
	{
		while (*lst)
		{
			del((*lst)->key);
			del((*lst)->value);
			old_elem = *lst;
			*lst = old_elem->next;
			free(old_elem);
		}
		*lst = NULL;
	}
}

void		env_update_next(t_envcopy *tmp, char *new_str)
{
	tmp->unset = 0;
	if (new_str == NULL)
	{
		free(tmp->value);
		tmp->value = NULL;
		tmp->sep = 0;
	}
}

void		env_update(t_param *all, char *str, char *new_str, int unset)
{
	t_envcopy	*tmp;

	tmp = all->env_new;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, str, ft_strlen(str) + 1))
		{
			if (unset == 1)
			{
				env_update_next(tmp, new_str);
			}
			if (new_str != NULL)
			{
				free(tmp->value);
				tmp->sep = 1;
				tmp->value = ft_strdup(new_str);
				return ;
			}
		}
		tmp = tmp->next;
	}
}

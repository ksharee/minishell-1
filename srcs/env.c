/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goodluck <goodluck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 23:10:32 by goodluck          #+#    #+#             */
/*   Updated: 2021/03/06 00:17:00 by goodluck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		env_add_back(t_envcopy **head, t_envcopy *new)
{
	t_envcopy	*tmp;

	tmp = *head;
	if (tmp == NULL)
		*head = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_envcopy	*env_new(char *key, char *value, int sep)
{
	t_envcopy	*elem;

	if (!(elem = malloc(sizeof(t_envcopy))))
		return (NULL);
	elem->key = ft_strdup(key);
	if (value != NULL)
		elem->value = ft_strdup(value);
	else
		elem->value = NULL;
	elem->sep = sep;
	elem->unset = 0;
	elem->next = NULL;
	return (elem);
}

int			env_run(t_param *all)
{
	int	i;

	i = -1;
	while (all->env_array[++i])
	{
		ft_putstr_fd(all->env_array[i], 1);
		write(1, "\n", 1);
	}
	return (0);
}

void		env_to_array(t_param *all)
{
	t_envcopy	*tmp;
	char		*str;
	int			i;

	free_array(all);
	tmp = all->env_new;
	i = -1;
	all->env_array = ft_calloc(env_size(all->env_new) + 1, sizeof(char *));
	while (tmp)
	{
		if (tmp->unset == 0)
		{
			if (tmp->sep == 1)
			{
				str = ft_strjoin_three(tmp->key, "=", tmp->value);
				all->env_array[++i] = ft_strdup(str);
				free(str);
			}
		}
		tmp = tmp->next;
	}
	all->env_array[++i] = NULL;
}

t_envcopy	*env_copy(char **envp, t_param *all)
{
	t_envcopy	*head;
	int			i;
	char		**env_array;

	head = NULL;
	i = -1;
	while (envp[++i])
	{
		env_array = ft_split(envp[i], '=');
		!ft_strncmp(env_array[0], "HOME", 5) ?
			all->tilda = ft_strdup(env_array[1]) : 0;
		env_add_back(&head, env_new(env_array[0], env_array[1], 1));
		free_split(env_array);
	}
	return (head);
}

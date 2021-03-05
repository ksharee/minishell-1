/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goodluck <goodluck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 12:42:52 by ksharee           #+#    #+#             */
/*   Updated: 2021/03/06 00:12:39 by goodluck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_envcopy **head)
{
	t_envcopy *old_elem;

	if (*head)
	{
		while (*head)
		{
			free((*head)->key);
			free((*head)->value);
			old_elem = *head;
			*head = old_elem->next;
			free(old_elem);
		}
		*head = NULL;
	}
}

void	swap_envcopy(t_envcopy **ptr, t_envcopy **b)
{
	t_envcopy	*tmp;

	tmp = *ptr;
	*ptr = tmp->next;
	tmp->next = (*ptr)->next;
	(*ptr)->next = tmp;
	*b = *ptr;
}

int		env_size(t_envcopy *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	shlvl_up(t_param *all)
{
	char	*str;
	int		i;

	str = env_search("SHLVL", all);
	if (!str)
		env_add_back(&all->env_new, env_new("SHLVL", "1", 1));
	else
	{
		i = ft_atoi(str);
		str = ft_itoa(++i);
		env_update(all, "SHLVL", str, 1);
		free(str);
	}
}

void	ft_lst_copy(t_param *all)
{
	t_envcopy	*tmp;
	t_envcopy	*head;

	head = NULL;
	tmp = all->env_new;
	while (tmp)
	{
		env_add_back(&head, env_new_copy(tmp->key,
			tmp->value, tmp->sep, tmp->unset));
		tmp = tmp->next;
	}
	all->env_copy = head;
}

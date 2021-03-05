/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goodluck <goodluck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 15:36:02 by ksharee           #+#    #+#             */
/*   Updated: 2021/03/05 22:09:23 by goodluck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		env_search_unset(t_param *all, char *key)
{
	t_envcopy	*tmp;

	tmp = all->env_new;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, ft_strlen(key) + 1))
			return (tmp->unset);
		tmp = tmp->next;
	}
	return (-1);
}

void	export_join(t_param *all, char *str)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	value = NULL;
	while (str[i] && str[i] != '+')
		i++;
	key = (char *)malloc(sizeof(char) * i);
	ft_strlcpy(key, str, i + 1);
	key[i] = '\0';
	value = ft_strdup(ft_strchr(str, '=') + 1);
	if (!env_search_all(key, all))
		env_add_back(&all->env_new, env_new(key, value, 1));
	else if (value != NULL)
		env_join(all, key, value, env_search_unset(all, key));
	free(key);
	free(value);
}

void	export_to_array(t_param *all)
{
	t_envcopy	*tmp;

	ft_lst_copy(all);
	sort_list(all);
	tmp = all->env_copy;
	while (tmp)
	{
		if (tmp->unset == 0)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(tmp->key, 1);
			tmp->sep == 1 ? write(1, "=", 1) : 0;
			if (tmp->value != NULL)
			{
				write(1, "\"", 1);
				ft_putstr_fd(tmp->value, 1);
				write(1, "\"", 1);
			}
			write(1, "\n", 1);
		}
		tmp = tmp->next;
	}
	free_env(&all->env_copy);
}

void	new_export(t_param *all, char *str)
{
	char	*key;
	char	*value;
	int		sep;
	int		i;

	i = 0;
	value = NULL;
	while (str[i] && str[i] != '=')
		i++;
	key = (char *)malloc(sizeof(char) * i);
	ft_strlcpy(key, str, i + 1);
	key[i] = '\0';
	if (str[i] == '=')
		sep = 1;
	else
		sep = 0;
	if (sep == 1)
		value = ft_strdup(ft_strchr(str, '=') + 1);
	if (!env_search_all(key, all))
		env_add_back(&all->env_new, env_new(key, value, sep));
	else if (value != NULL || env_search_unset(all, key) == 1)
		env_update(all, key, value, 1);
	free(key);
	free(value);
}

int		export_run(t_param *all)
{
	int	i;

	i = 0;
	if (size_arg(all) == 1)
		export_to_array(all);
	else
	{
		while (all->line[++i])
		{
			if (check_line(all->line[i]) == 1)
			{
				error("export: ", all->line[i], "not a valid identifier");
				continue ;
			}
			if (check_line(all->line[i]) == 2)
				export_join(all, all->line[i]);
			else
				new_export(all, all->line[i]);
		}
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharee <ksharee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 12:55:35 by ksharee           #+#    #+#             */
/*   Updated: 2021/03/05 13:23:02 by ksharee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envcopy	*env_new_copy(char *key, char *value, int sep, int unset)
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
	elem->unset = unset;
	elem->next = NULL;
	return (elem);
}

int			is_num_char(char *str)
{
	int	i;

	i = -1;
	str[0] == '-' ? i++ : 0;
	while (str[++i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
	}
	return (0);
}

int			size_arg(t_param *all)
{
	int	i;

	i = 0;
	while (all->line[i])
		i++;
	return (i);
}

char		*get_exit_status(t_param *all)
{
	int	tmp;

	(void)all;
	tmp = g_exit.exit;
	g_exit.exit = 0;
	return (ft_itoa(tmp));
}

int			pid_init(pid_t *pid)
{
	if ((*pid = fork()) == -1)
	{
		error("fork: ", "", strerror(errno));
		g_exit.exit = 1;
		return (0);
	}
	return (1);
}

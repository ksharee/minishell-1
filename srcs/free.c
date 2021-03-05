/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleonel <pleonel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 23:46:01 by goodluck          #+#    #+#             */
/*   Updated: 2021/03/04 15:05:12 by pleonel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **split)
{
	int size;
	int i;

	size = 0;
	i = -1;
	while (split[++i])
		size++;
	while (size)
	{
		free(split[--i]);
		size--;
	}
	free(split);
	split = NULL;
}

void	free_array(t_param *all)
{
	int i;

	i = -1;
	if (all->env_array == NULL)
		return ;
	while (all->env_array[++i])
	{
		free(all->env_array[i]);
	}
	free(all->env_array);
}

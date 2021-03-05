/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_spec_syms.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharee <ksharee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 13:06:58 by pleonel           #+#    #+#             */
/*   Updated: 2021/03/05 15:51:41 by ksharee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parsing_quotes(char *line, char **arg, int i, t_param *all)
{
	i++;
	all->is_quote = 1;
	while (line[i] && line[i] != '\'')
	{
		ft_str_add_back(arg, line[i]);
		i++;
	}
	return (i + 1);
}

char	*ft_make_one_space(char *str)
{
	char	*res;
	char	*tmp;
	char	**array;
	int		i;

	i = 0;
	array = ft_split(str, ' ');
	res = ft_strdup(array[0]);
	if (array[0])
		while (array[++i])
		{
			tmp = res;
			res = ft_strjoin(res, " ");
			free(tmp);
			tmp = res;
			res = ft_strjoin(res, array[i]);
			free(tmp);
		}
	free_split(array);
	return (res);
}

int		parsing_env_variable(t_param *all, char *line, char **arg, int i)
{
	char *var;
	char *res;

	var = (char*)calloc(1, sizeof(char));
	if (!ft_isdigit(line[i + 1]) && line[i + 1] != '?')
		while (ft_isalnum(line[++i]))
			ft_str_add_back(&var, line[i]);
	else if (ft_isdigit(line[i + 1]) || line[i + 1] == '?')
		ft_str_add_back(&var, line[(i += 2) - 1]);
	else
		ft_str_add_back(arg, line[i++]);
	res = (ft_strncmp(var, "?", 2) ? env_search(var, all) \
		: get_exit_status(all));
	free(var);
	if (res != NULL || line[i - 1] == '$')
	{
		res = ft_make_one_space(res);
		var = (res != NULL ? ft_strjoin((*arg), res) : ft_strdup("$"));
		free(res);
		free(*arg);
		(*arg) = var;
	}
	return (i);
}

int		parsing_dub_quotes(t_param *all, char *line, char **arg, int i)
{
	i++;
	all->is_quote = 1;
	while (line[i] && line[i] != '"')
	{
		if (line[i] == '\\' && ft_strchr("$\\\"`", line[i + 1]) && line[i + 1])
		{
			ft_str_add_back(arg, line[i + 1]);
			i += 2;
		}
		else if (line[i] == '$')
			i = parsing_env_variable(all, line, arg, i);
		else
			ft_str_add_back(arg, line[i++]);
	}
	return (i + 1);
}

int		parsing_redirections(t_param *all, char *line, int i, char **arg)
{
	if (line[i - 1] != ' ')
		adding_next_arg(all, line, i, arg);
	if (line[i] == '>' && line[i + 1] == '>')
	{
		all->is_redirect = 3;
		i++;
	}
	else if (line[i] == '>')
		all->is_redirect = 1;
	else
		all->is_redirect = 2;
	i++;
	while (line[i] == ' ' && line[i])
		i++;
	return (i);
}

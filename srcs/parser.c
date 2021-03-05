/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharee <ksharee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:39:52 by pleonel           #+#    #+#             */
/*   Updated: 2021/03/05 15:31:07 by ksharee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "minishell.h"

int		adding_next_arg(t_param *all, char *line, int i, char **arg)
{
	if (((*arg)[0] && all->is_redirect == 0) || all->is_quote)
		ft_line_add_back(&(all->line), arg);
	else if ((*arg)[0])
		i = redirect_file(all, arg, i, line);
	all->is_quote = 0;
	return (i);
}

int		break_parsing(t_param *all, char *line, int i, char **arg)
{
	all->pipe_flag = (line[i] == '|');
	i = adding_next_arg(all, line, i, arg);
	free(*arg);
	return (i + 1);
}

int		iter_line(t_param *all, char *line, int i, char **arg)
{
	if (line[i] == '\\' && line[i + 1] != '\0')
	{
		ft_str_add_back(arg, line[++i]);
		i++;
	}
	else if (line[i] == '\'')
		i = parsing_quotes(line, arg, i, all);
	else if (line[i] == '\"')
		i = parsing_dub_quotes(all, line, arg, i);
	else if (line[i] == '>' || line[i] == '<')
		i = parsing_redirections(all, line, i, arg);
	else if (line[i] == '$')
		i = parsing_env_variable(all, line, arg, i);
	else if (line[i] == ' ' && !(i != 0 && line[i - 1] == '\\'))
	{
		i = adding_next_arg(all, line, i, arg);
		while (line[i] == ' ' && line[i])
			i++;
	}
	else if (line[i] != '\\')
		ft_str_add_back(arg, line[i++]);
	else
		i++;
	return (i);
}

int		parsing(t_param *all, char *line, int i)
{
	char	*arg;

	all->pipe_flag = 0;
	all->line = (char**)ft_calloc(1, sizeof(char*));
	all->is_redirect = 0;
	all->is_quote = 0;
	arg = (char*)calloc(1, sizeof(char));
	if (is_correct_syntax(all, line))
		while (line[i])
		{
			if (line[i] == '|' || line[i] == ';')
				return (break_parsing(all, line, i, &arg));
			else
				i = iter_line(all, line, i, &arg);
		}
	i = adding_next_arg(all, line, i, &arg);
	free(arg);
	return (0);
}

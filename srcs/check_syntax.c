/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharee <ksharee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 12:58:36 by pleonel           #+#    #+#             */
/*   Updated: 2021/03/05 15:29:35 by ksharee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_correct_quotes(int i, char *line, t_param *all)
{
	int	j;

	j = i + 1;
	while ((line[j] != line[i] || line[j - 1] == '\\') && line[j])
		j++;
	if (line[j] == '\0')
		return (ft_error(SYNT_ERR_STR, all, SYNTAX_ERROR, ""));
	else
		i = j + 1;
	return (i);
}

int		is_correct_spec_syms(int i, char *line, t_param *all, int is_char)
{
	int j;

	j = i;
	if (line[i] == '>' && line[i + 1] == '>')
		i++;
	i++;
	while (line[i] == ' ' && line[i])
		i++;
	if ((ft_strchr("><|;", line[i]) && ft_strchr("><", line[j]) && line[i]) || \
		(ft_strchr("|;", line[i]) && ft_strchr("|;", line[j]) && line[i]) || \
		(!line[i] && line[j] != ';') || (ft_strchr("|;", line[j]) && !is_char))
	{
		ft_error(SYNT_ERR_STR, all, SYNTAX_ERROR, "");
		return (0);
	}
	return (i);
}

int		is_correct_syntax(t_param *all, char *line)
{
	int	i;
	int	is_char;

	i = 0;
	is_char = 0;
	while (line[i])
	{
		if (ft_strchr("()&`", line[i]) && \
			(i == 0 || line[i - 1] != '\\'))
		{
			ft_error(SYNT_ERR_STR, all, SYNTAX_ERROR, "");
			return (0);
		}
		if (ft_strchr("\"\'", line[i]) && \
				(i == 0 || line[i - 1] != '\\'))
			i = is_correct_quotes(i, line, all);
		else if (ft_strchr("><|;", line[i]) && \
			(i == 0 || line[i - 1] != '\\'))
			i = is_correct_spec_syms(i, line, all, is_char);
		else
			is_char = (line[i++] == ' ' && is_char == 0) ? 0 : i;
		if (i == 0)
			return (0);
	}
	return (1);
}

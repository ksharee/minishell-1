/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharee <ksharee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 13:04:21 by pleonel           #+#    #+#             */
/*   Updated: 2021/03/05 10:38:00 by ksharee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_strstrlen(char **line)
{
	int i;

	i = 0;
	if (line == NULL)
		return (0);
	while (line[i])
		i++;
	return (i);
}

void	ft_line_add_back(char ***line, char **last)
{
	char	**line_tmp;
	int		i;
	int		new_len;

	new_len = (ft_strstrlen(*line) + 1);
	line_tmp = (char**)malloc(sizeof(char*) * (new_len + 1));
	line_tmp[new_len] = NULL;
	line_tmp[new_len - 1] = *last;
	i = -1;
	while ((*line)[++i] != NULL)
		line_tmp[i] = (*line)[i];
	free(*line);
	*line = line_tmp;
	*last = (char*)calloc(1, sizeof(char));
}

void	ft_str_add_back(char **str, char last)
{
	char	*str_tmp;
	int		i;
	int		new_str;

	new_str = (ft_strlen(*str) + 1);
	str_tmp = (char*)malloc(sizeof(char) * (new_str + 1));
	str_tmp[new_str] = '\0';
	str_tmp[new_str - 1] = last;
	i = -1;
	while ((*str)[++i] != '\0')
		str_tmp[i] = (*str)[i];
	free(*str);
	(*str) = str_tmp;
}

int		ft_error(char *message, t_param *all, int err, char *param)
{
	(void)all;
	g_exit.exit = err;
	error(param, "", message);
	return (0);
}

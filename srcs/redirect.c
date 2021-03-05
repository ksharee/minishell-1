/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharee <ksharee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:30:51 by ksharee           #+#    #+#             */
/*   Updated: 2021/03/05 15:32:30 by ksharee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_file(char *file, t_param *all)
{
	if (all->is_redirect == 1)
		all->fd_redir = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (all->is_redirect == 2)
		all->fd_redir = open(file, O_RDONLY);
	else if (all->is_redirect == 3)
		all->fd_redir = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
}

int		redirect_file(t_param *all, char **arg, int i, char *line)
{
	char	*file;

	file = *arg;
	open_file(file, all);
	if (all->fd_redir == -1)
	{
		ft_error(strerror(errno), all, errno, file);
		ft_free_all_line(all);
		all->line = (char**)ft_calloc(1, sizeof(char*));
		while (line[i] && !ft_strchr(";|", line[i]))
			i++;
		free(file);
		file = ft_strdup("");
		return (i);
	}
	all->is_redirect == 2 ? dup2(all->fd_redir, 0) : dup2(all->fd_redir, 1);
	all->redirect_size = 1;
	all->is_redirect = 0;
	free(*arg);
	*arg = (char*)calloc(1, sizeof(char));
	return (i);
}

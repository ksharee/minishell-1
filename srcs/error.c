/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharee <ksharee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 11:24:06 by ksharee           #+#    #+#             */
/*   Updated: 2021/03/04 18:16:23 by ksharee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(char *command, char *param, char *error)
{
	ft_putstr_fd("\e[1;31mMiniShell: \e[0m", 2);
	ft_putstr_fd(command, 2);
	if (!ft_strncmp(command, "export: ", 8) ||
		!ft_strncmp(command, "unset: ", 8))
		write(2, "`", 1);
	ft_putstr_fd(param, 2);
	if (!ft_strncmp(command, "export: ", 8) ||
		!ft_strncmp(command, "unset: ", 8))
		write(2, "'", 1);
	param != NULL ? ft_putstr_fd(": ", 2) : 0;
	ft_putstr_fd(error, 2);
	write(2, "\n", 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharee <ksharee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 10:51:39 by ksharee           #+#    #+#             */
/*   Updated: 2021/03/05 10:22:39 by ksharee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_run(t_param *all)
{
	char	pwd[1000];

	if (getcwd(pwd, 1000) == NULL)
		ft_putstr_fd(env_search("PWD", all), 1);
	else
		ft_putstr_fd(pwd, 1);
	write(1, "\n", 1);
	return (0);
	(void)all;
}

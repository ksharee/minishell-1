/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharee <ksharee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 23:17:48 by goodluck          #+#    #+#             */
/*   Updated: 2021/03/04 11:06:50 by ksharee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_ctrd(void)
{
	ft_putstr_fd("exit\n", 1);
	exit(0);
}

void	sig_catcher_exec(int num)
{
	if (num == SIGQUIT && g_exit.mini == 0)
	{
		ft_putstr_fd("Quit: 3\n", 2);
		g_exit.exit = CTRL_BKSLSH;
		g_exit.is_signal = 1;
	}
	else if (num == SIGINT && g_exit.mini == 0)
	{
		g_exit.exit = CTRL_C;
		g_exit.is_signal = 3;
		ft_putstr_fd("\n", 2);
	}
}

void	sig_catcher_minishell(int num)
{
	ft_putstr_fd("\b\b  \b\b", 2);
	if (num == SIGINT && g_exit.mini == 0)
	{
		g_exit.exit = CTRL_C;
		g_exit.is_signal = 3;
		ft_putstr_fd("\n", 2);
		display_msg();
	}
}

void	signal_init(void)
{
	if (signal(SIGINT, sig_catcher_minishell) == SIG_ERR)
		exit(ERROR_SIGINT);
	if (signal(SIGQUIT, sig_catcher_minishell) == SIG_ERR)
		exit(ERROR_SIGQUIT);
}

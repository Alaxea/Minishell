/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ctrl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:11:32 by astefans          #+#    #+#             */
/*   Updated: 2024/11/15 12:46:04 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_sigquit(int signal)
{
	if (signal == SIGTERM)
	{
		exit(0);
	}
}

void	handle_sigint(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	setup_signals(void)
{
        signal(SIGQUIT, SIG_IGN);
        signal(SIGINT, handle_sigint);
        signal(SIGTERM, handle_sigquit);
}

void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, handle_sigquit);
    signal(SIGTERM, SIG_IGN);
}

void	default_signals(void)
{
	signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    signal(SIGTERM, SIG_DFL);
}

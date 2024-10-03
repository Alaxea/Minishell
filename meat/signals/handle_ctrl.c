/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ctrl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:11:32 by astefans          #+#    #+#             */
/*   Updated: 2024/08/31 14:46:52 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
void	handle_sigquit(int signal)
{
	if (signal == SIGQUIT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		write(1, "exit\n", 5);
		exit(0);
	}
}

//handle ctrl-c
void	handle_sigint(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
void	run_signals(int signal)
{
	if (signal == 1)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	if (signal == 2)
		handle_sigquit(signal);
}*/

static void handle_sigquit(int signal)
{
	if (signal)
		exit(EXIT_FAILURE);
}

static void	handle_sigint(int signal)
{
	if (signal)
	{
		rl_replace_line("", 0);
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
}
void	run_signals(void)
{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, handle_sigquit);
}
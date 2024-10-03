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
int put_ret_num;

void	restore_prompt(int sig)
{
	//exit status code in Linux systems,
	//indicating that a process was terminated by signal 2(SIGINT-ctrl-c)
	put_ret_num = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}
void	ctrl_c(int sig)
{
	put_ret_num = 130;
	write(1, "\n", 1);
	(void)sig;
}
void	backslash(int sig)
{
	put_ret_num = 131;
	write(1, "\n", 1);
	(void)sig;
}
*/

//handle ctrl-d
void	handle_sigquit(int sig)
{
	if (sig == SIGQUIT)
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
void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
void	run_signals(int sig)
{
	if (sig == 1)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == 2)
		handle_sigquit(sig);
}
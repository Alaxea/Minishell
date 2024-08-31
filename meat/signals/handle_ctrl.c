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
void	run_signals(int sig)
{
	if (sig == 1)
	{
		signal(SIGINT, restore_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == 2)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, backslash);
	}
	if (sig == 3)
	{
		printf("exit\n");
		exit(0);
	}
}
int main_function()
{
	run_signals(1);

	while(1)
	{
		char *input;

		input = readline("minishell>> ");
		if(!input)
		{
			printf("exit\n");
			break;
		}
		if(*input != '\0')
		{
			write(1, "exit\n", 5);
			break;
		}
		if (ft_strlen(input) > 0)
            add_history(input);
		free(input);
	}
	return(0);
}
//handle ctrl-d
/*void	handle_sigquit(int sig)
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

int main()
{
	signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN); //sig_ign to do nothing when is backslash
	while(1)
	{
		char *input;
		input = readline("minishell>> ");
		if(input == NULL)
		{
			write(1, "exit\n", 5);
			break;
		}
		free(input);
	}
	return(0);
}
//to do:handle ctrl-d when user writes something after prompt*/
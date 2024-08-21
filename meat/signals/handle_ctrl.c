/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ctrl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:11:32 by astefans          #+#    #+#             */
/*   Updated: 2024/08/20 16:19:51 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int main()
{
	signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN); /*sig_ing to do nothing when is ctrl-\*/
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

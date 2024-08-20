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

#include "minishell.h"

/*handle ctrl-c*/
/*void  handle_sigint(int sig)
{
	(void)sig;

	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}*/
/*handle ctrl-\*/
void	do_nothing(int sig)
{
	if (sig == 2)
		printf("\n");
}

void	handle_sigint(int sig)
{
	(void)sig;
	if (sig == 2)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_redisplay();
	}
}
void handle_sigquit(int sig)
{
    (void)sig;
	do_nothing(sig);
}

int main()
{
	signal(SIGINT, handle_sigint);
    signal(SIGQUIT, handle_sigquit);
	while(1)
	{
		char *input;
		input = readline("minishell>> ");
		if(input == NULL)
		{
			printf("Exiting minishell...\n");
			break;
		}
		free(input);
	}
	return(0);
}

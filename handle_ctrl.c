/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ctrl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:11:32 by astefans          #+#    #+#             */
/*   Updated: 2024/08/20 11:11:35 by astefans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*handle ctrl-c*/
void  handle_sigint(int sig)
{
	(void)sig;
	printf("\nminishell>> ");
}
/*handle ctrl-\*/
void handle_sigquit(int sig)
{
    (void)sig;
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

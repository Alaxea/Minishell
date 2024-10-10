/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:25:19 by astefans          #+#    #+#             */
/*   Updated: 2024/10/07 22:57:29 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_pipe(t_simple_cmd *current)
{
	if (current->prev == NULL && current->next != NULL)
		dup2(current->fd_out, STDOUT_FILENO);
	if (current->prev != NULL && current->next != NULL)
	{
		dup2(current->prev->fd_in, STDIN_FILENO);
		dup2(current->fd_out, STDOUT_FILENO);
	}
	if (current->next == NULL && current->prev != NULL)
		dup2(current->prev->fd_in, STDIN_FILENO);
}

void	create_pipes(t_data *commands, t_data *env)
{
	int i;

	i = 0;
	while(commands[i].command)
	{
		if (pipe(commands[i].fd) < 0)
			exit_shell(env, "Filed to create a pipe\n", 2);
		i++;
	}
}

void	close_fds_main(t_data *commands)
{
	int i;

	i = 0;
	while (commands[i].command)
	{
		close(commands[i].fd[0]);
		close(commands[i].fd[1]);
		i++;
	}
}

void	close_fds_child(t_data *commands, int i)
{
	int j;

	j = 0;
	while (commands[j].command)
	{
		if (i != j)
			close(commands[j].fd[1]);
		if (i - 1 != j)
			close(commands[j].fd[0]);
		j++;
	}
}

int		waiting_and_result(t_data *commands, t_data *env)
{
	int i;
	int result;

	i = -1;
	while (commands[++i].command)
		wait(&result);
	if (commands[i - 1].pid == 0)
		return(env -> last_result);
	return(WEXITSTATUS(result) % 255);
}

void	fork_child(t_data *env, t_data *commands, int i)
{
	commands[i].pid = fork();
	if (commands[i].pid == -1)
		exit_shell(env, "Filed to create a fork\n", 2);
	if (commands[i].pid == 0)
	{
		close_fds_child(commands, i);
		redir_check(&(commands[i].simple_cmds[0]));
		if (commands[i + 1].command)
			dup2(commands[i].fd[1], STDOUT_FILENO);
		if (i != 0)
			dup2(commands[i - 1].fd[0], STDIN_FILENO);
		env->last_result = execute_builtin(&commands[i]);
		close(commands[i].fd[1]);
		if (i != 0)
			close(commands[i - 1].fd[0]);
		exit(env->last_result % 255);
	}
}
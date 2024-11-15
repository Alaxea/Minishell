/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:01:19 by astefans          #+#    #+#             */
/*   Updated: 2024/11/15 16:39:54 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	execute_builtin_fork(t_simple_cmd *current, t_data *env)
{
	int	ret;

	if (redir_check(current) == -1)
		exit(1);
	if (current->fd_in > 2)
		dup2(current->fd_in, STDIN_FILENO);
	if (current->fd_out > 2)
		dup2(current->fd_out, STDOUT_FILENO);
	ret = execute_builtin(env, current);
	exit(ret);
}

static int	execute_external_fork(t_simple_cmd *current,
		t_data *env, char *full_path)
{
	if (redir_check(current) == -1)
		exit(1);
	close_pipes(current);
	execve(full_path, current->cmd, env->envp);
	perror("execve");
	free(full_path);
	exit(127);
}

void	setup_redirection(t_simple_cmd *current)
{
	if (current->fd_in > 2)
		dup2(current->fd_in, STDIN_FILENO);
	if (current->fd_out > 2)
		dup2(current->fd_out, STDOUT_FILENO);
	redir_check(current);
}

static void	close_fds(t_simple_cmd *current)
{
	if (current->fd_in > 2)
		close(current->fd_in);
	if (current->fd_out > 2)
		close(current->fd_out);
}

int	fork_and_execute(t_simple_cmd *cmd, t_data *env)
{
	t_simple_cmd	*current;
	int				status;
	char			*full_path;

	current = cmd;
	while (current)
	{
		if (check_for_builtins(current))
		{
			current->pid = fork();
			if (current->pid == 0)
				execute_builtin_fork(current, env);
			return (waitpid(current->pid, &status, 0), WEXITSTATUS(status));
		}
		full_path = get_full_path(current->cmd[0], env->envp);
		if (!full_path)
			return (error_command_not_found());
		current->pid = fork();
		if (current->pid == 0)
			execute_external_fork(current, env, full_path);
		free(full_path);
		close_fds(current);
		current = current->next;
	}
	return (0);
}

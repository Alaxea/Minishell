/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:01:19 by astefans          #+#    #+#             */
/*   Updated: 2024/11/22 11:36:10 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	execute_single_command(t_simple_cmd *current, t_data *env)
{
	int		status;
	char	*full_path;

	current->pid = fork();
	if (current->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, handle_sigquit);
		signal(SIGTERM, SIG_DFL);
		if (redir_check(current) == -1)
			exit(1);
		if (check_for_builtins(current))
			exit(execute_builtin(env, current));
		full_path = get_full_path(current->cmd[0], env->envp);
		if (!full_path)
			exit(127);
		execve(full_path, current->cmd, env->envp);
		perror("execve");
		free(full_path);
		exit(127);
	}
	waitpid(current->pid, &status, 0);
	return (WEXITSTATUS(status));
}

static void	close_other_fds(t_simple_cmd *cmd, t_simple_cmd *current)
{
	t_simple_cmd	*buf;

	buf = cmd;
	while (buf)
	{
		if (buf != current)
		{
			if (buf->fd_in > 2)
				close(buf->fd_in);
			if (buf->fd_out > 2)
				close(buf->fd_out);
		}
		buf = buf->next;
	}
}

static void	execute_child_command(t_simple_cmd *current,
		t_simple_cmd *cmd, t_data *data)
{
	char	*full_path;
	int		code;

	default_signals();
	close_other_fds(cmd, current);
	redir_check(current);
	setup_redirection(current);
	if (check_for_builtins(current))
	{
		code = execute_builtin(data, current);
		clean_builtin(data);
		exit(code);
	}
	full_path = get_full_path(current->cmd[0], data->envp);
	if (!full_path)
		exit(127);
	execve(full_path, current->cmd, data->envp);
	perror("execve");
	free(full_path);
	exit(127);
}

static void	wait_for_all(t_simple_cmd *cmd, int *status)
{
	while (cmd)
	{
		waitpid(cmd->pid, status, 0);
		cmd = cmd->next;
	}
}

int	execute(t_simple_cmd *cmd, t_data *env)
{
	t_simple_cmd	*current;
	int				status;

	current = cmd;
	status = 0;
	ignore_signals();
	if (!current)
		return (-1);
	if (!cmd->next)
		return (execute_single_command(current, env));
	if (create_pipes(env, cmd) == -1)
		return (-1);
	while (current)
	{
		current->pid = fork();
		if (current->pid == 0)
		{
			default_signals();
			execute_child_command(current, cmd, env);
		}
		current = current->next;
	}
	close_pipes(cmd);
	wait_for_all(cmd, &status);
	return (WEXITSTATUS(status));
}

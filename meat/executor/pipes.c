/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:01:19 by astefans          #+#    #+#             */
/*   Updated: 2024/11/10 11:23:57 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	close_pipes(t_simple_cmd *cmd)
{
	t_simple_cmd	*current;
	int				fd_in;
	int				fd_out;

	current = cmd;
	while (current)
	{
		fd_in = current->fd_in;
		fd_out = current->fd_out;
		if (fd_in > 2)
		{
			close(fd_in);
			current->fd_in = -1;
		}
		if (fd_out > 2)
		{
			close(fd_out);
			current->fd_out = -1;
		}
		current = current->next;
	}
}

int	create_pipes(t_data *env, t_simple_cmd *cmd)
{
	t_simple_cmd	*current;

	current = cmd;
	while (current->next)
	{
		if (pipe(env->fd) == -1)
		{
			perror("pipe");
			return (-1);
		}
		current->fd_out = env->fd[1];
		current->next->fd_in = env->fd[0];
		current = current->next;
	}
	return (0);
}

int	execute(t_simple_cmd *cmd, t_data *env)
{
	t_simple_cmd	*current;
	t_simple_cmd	*temp;
	int				status;
	int				ret;
	char			*full_path;

	current = cmd;
	status = 0;
	if (!current)
		return (-1);
	if (!cmd->next)
	{
		current->pid = fork();
		if (current->pid == 0)
		{
			if (redir_check(current) == -1)
				exit(1);
			if (check_for_builtins(current))
			{
				ret = execute_builtin(env, current);
				exit(ret);
			}
			else
			{
				full_path = get_full_path(current->cmd[0], env->envp);
				if (!full_path)
				{
					ft_putstr_fd("Command not found\n", 2);
					exit(127);
				}
				execve(full_path, current->cmd, env->envp);
				perror("execve");
				free(full_path);
				exit(127);
			}
		}
		waitpid(current->pid, &status, 0);
		return (WEXITSTATUS(status));
	}
	if (create_pipes(env, cmd) == -1)
		return (-1);
	while (current)
	{
		current->pid = fork();
		if (current->pid == 0)
		{
			temp = cmd;
			while (temp)
			{
				if (temp != current)
				{
					if (temp->fd_in > 2)
						close(temp->fd_in);
					if (temp->fd_out > 2)
						close(temp->fd_out);
				}
				temp = temp->next;
			}
			if (current->fd_in > 2)
			{
				dup2(current->fd_in, STDIN_FILENO);
				close(current->fd_in);
			}
			if (current->fd_out > 2)
			{
				dup2(current->fd_out, STDOUT_FILENO);
				close(current->fd_out);
			}
			if (check_for_builtins(current))
				exit(execute_builtin(env, current));
			else
			{
				full_path = get_full_path(current->cmd[0], env->envp);
				if (!full_path)
				{
					ft_putstr_fd("Command not found\n", 2);
					exit(127);
				}
				execve(full_path, current->cmd, env->envp);
				perror("execve");
				free(full_path);
				exit(127);
			}
		}
		current = current->next;
	}
	close_pipes(cmd);
	current = cmd;
	while (current)
	{
		waitpid(current->pid, &status, 0);
		current = current->next;
	}
	return (WEXITSTATUS(status));
}

int	fork_and_execute(t_simple_cmd *cmd, t_data *env)
{
	t_simple_cmd	*current;
	char			*full_path;
	int				status;
	int				ret;

	current = cmd;
	while (current)
	{
		if (check_for_builtins(current))
		{
			write(STDOUT_FILENO, "", 0);
			write(STDERR_FILENO, "", 0);
			current->pid = fork();
			if (current->pid == 0)
			{
				if (redir_check(current) == -1)
					exit(1);
				if (current->fd_in > 2)
					dup2(current->fd_in, STDIN_FILENO);
				if (current->fd_out > 2)
					dup2(current->fd_out, STDOUT_FILENO);
				ret = execute_builtin(env, current);
				exit(ret);
			}
			if (current->pid < 0)
			{
				perror("fork");
				return (-1);
			}
			if (current->fd_in > 2)
				close(current->fd_in);
			if (current->fd_out > 2)
				close(current->fd_out);
			waitpid(current->pid, &status, 0);
			return (WEXITSTATUS(status));
		}
		else
		{
			full_path = get_full_path(current->cmd[0], env->envp);
			if (!full_path)
			{
				ft_putstr_fd("Command not found\n", 2);
				return (-1);
			}
			current->pid = fork();
			if (current->pid == 0)
			{
				if (redir_check(current) == -1)
				{
					exit(1);
				}
				close_pipes(cmd);
				execve(full_path, current->cmd, env->envp);
				perror("execve");
				free(full_path);
				exit(127);
			}
			if (current->pid < 0)
			{
				perror("fork");
				free(full_path);
				return (-1);
			}
			free(full_path);
		}
		if (current->fd_in > 2)
			close(current->fd_in);
		if (current->fd_out > 2)
			close(current->fd_out);
		current = current->next;
	}
	return (0);
}

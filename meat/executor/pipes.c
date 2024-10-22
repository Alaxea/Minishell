/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:25:19 by astefans          #+#    #+#             */
/*   Updated: 2024/10/17 21:46:18 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*void	handle_pipe(t_simple_cmd *current)
{
	if (current->prev == NULL && current->next != NULL)
		dup2(data->fd[1], STDOUT_FILENO);
	if (current->prev != NULL && current->next != NULL)
	{
		dup2(data->fd[0], STDIN_FILENO);
		dup2(data->fd[1], STDOUT_FILENO);
	}
	if (current->next == NULL && current->prev != NULL)
		dup2(data->fd[0], STDIN_FILENO);
}

void	create_pipes(t_simple_cmd *commands, t_data *env)
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

void	close_pipes(t_simple_cmd *hell)
{
	int	i;

	i = 0;
	while (hell->simple_cmds[i].cmd)
	{
		close(env->fd[0]);
		close(env->fd[1]);
		i++;
	}
}

void	close_fds_main(t_simple_cmd *commands)
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

void	close_fds_child(t_simple_cmd *commands, int i)
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

int		waiting_and_result(t_simple_cmd *commands, t_data *env)
{
	int i;
	int result;

	(void)env;
	i = -1;
	while (commands[i].cmd)
	{
        if (commands[i].pid > 0)
            waitpid(commands[i].pid, &result, 0);
	}
	return(WEXITSTATUS(result) % 255);
}

void	fork_child(t_data *env, t_simple_cmd *commands, int i)
{
	t_simple_cmd *cmd;
	
	commands[i].pid = fork();
	if (commands[i].pid == -1)
		exit_shell(env, "Filed to create a fork\n", 2);
	if (commands[i].pid == 0)
	{
		close_fds_child(commands, i);
		redir_check(&(commands[i].cmd[0]));
		if (commands[i + 1].command)
			dup2(commands[i].fd[1], STDOUT_FILENO);
		if (i != 0)
			dup2(commands[i - 1].fd[0], STDIN_FILENO);
		env->last_result = execute_builtin(env, &cmd[i]);
		close(commands[i].fd[1]);
		if (i != 0)
			close(commands[i - 1].fd[0]);
		exit(env->last_result % 255);
	}
}

void	execute(t_data *env, t_simple_cmd *cmd)
{
	int	i;
	int	result;

	//create_pipes(hell, env);
	i = 0;
	while (cmd[i].cmd)
	{
		result = execute_command(&cmd[i], env->env_var);
		env->last_result = result;
		if (result == -1)
			fork_child(env, cmd, i);
		else
			env->last_result = result;
		printf("%d\n", i);
		i++;

	}
	close_pipes(env);
	env->last_result = waiting_and_result(cmd, env);
}*/

void close_pipes(t_simple_cmd *cmd)
{
    while (cmd)
    {
        if (cmd->fd_in > 0)
            close(cmd->fd_in);
        if (cmd->fd_out > 0)
            close(cmd->fd_out);
        cmd = cmd->next;
    }
}

int create_pipes(t_data *env, t_simple_cmd *cmd)
{
    t_simple_cmd *current = cmd;

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

int fork_and_execute(t_simple_cmd *cmd, t_data *env)
{
    t_simple_cmd *current = cmd;

    while (current)
    {
        current->pid = fork();
        if (current->pid == -1)
        {
            perror("fork");
            return (-1);
        }
        if (current->pid == 0) // Proces potomny
        {
            if (current->fd_in > 0)
            {
                dup2(current->fd_in, STDIN_FILENO);
                close(current->fd_in);
            }
            if (current->fd_out > 0)
            {
                dup2(current->fd_out, STDOUT_FILENO);
                close(current->fd_out);
            }
            close_pipes(cmd);
            if (execve(current->cmd[0], current->cmd, env->envp) == -1)
            {
                perror("execve");
                exit(127);
            }
        }
		else if (current->fd_in > 0)
        {
            close(current->fd_in);  // Rodzic zamyka fd_in, gdy dziecko skończy
        }

        if (current->fd_out > 0)
        {
            close(current->fd_out);  // Rodzic zamyka fd_out po stworzeniu pipe'a
        }
        current = current->next;
    }

    return (0);
}

int execute(t_simple_cmd *cmd, t_data *env)
{
	t_simple_cmd *current;
	int status;

	current = cmd;
    if (create_pipes(env, cmd) == -1)
        return (-1);
    if (fork_and_execute(cmd, env) == -1)
        return (-1);
    close_pipes(cmd);
    while (current)
    {
        waitpid(current->pid, &status, 0);
        if (WIFEXITED(status))
            env->last_result = WEXITSTATUS(status);
        current = current->next;
    }
    return (env->last_result);
}


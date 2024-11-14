/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:15:43 by astefans          #+#    #+#             */
/*   Updated: 2024/11/14 15:33:44 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*int	search_in_path(t_data *env, t_simple_cmd *cmd)
{
	char	*bin_path;
	char	**path;
	char	*tmp;
	int		ret_val;

	if (cmd->cmd && (cmd->cmd[0][0] == '.' || cmd->cmd[0][0] == '/'))
	{
		bin_path = find_script(cmd->cmd[0], env);
		return (execute_path(bin_path, env, cmd));
	}
	tmp = set_env_var(env, "PATH");
	if (!tmp)
	{
		ft_putstr_fd("PATH not found\n", 2);
		return (127);
	}
	ft_putstr_fd("PATH: ", 2);
	ft_putstr_fd(tmp, 2);
	ft_putstr_fd("\n", 2);
	path = ft_split(tmp, ':');
	free(tmp);
	ft_putstr_fd("Looking for command: ", 2);
	ft_putstr_fd(cmd->cmd[0], 2);
	ft_putstr_fd("\n", 2);
	bin_path = NULL;
	ret_val = find_binary(env, cmd, bin_path, path);
	if (ret_val == 127)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putstr_fd(cmd->cmd[0], 2);
		ft_putstr_fd("\n", 2);
		free_paths(path);
	}
	return (ret_val);
}*/

static int	handle_absolute_path(t_data *env, t_simple_cmd *cmd)
{
	char	*bin_path;

	bin_path = find_script(cmd->cmd[0], env);
	return (execute_path(bin_path, env, cmd));
}

static char	**get_path_dirs(t_data *env)
{
	char	*tmp;
	char	**path;

	tmp = set_env_var(env, "PATH");
	if (!tmp)
	{
		ft_putstr_fd("PATH not found\n", 2);
		return (NULL);
	}
	ft_putstr_fd("PATH: ", 2);
	ft_putstr_fd(tmp, 2);
	ft_putstr_fd("\n", 2);
	path = ft_split(tmp, ':');
	free(tmp);
	return (path);
}

int	search_in_path(t_data *env, t_simple_cmd *cmd)
{
	char	*bin_path;
	char	**path;
	int		ret_val;

	if (cmd->cmd && (cmd->cmd[0][0] == '.' || cmd->cmd[0][0] == '/'))
		return (handle_absolute_path(env, cmd));
	path = get_path_dirs(env);
	if (!path)
		return (127);
	ft_putstr_fd("Looking for command: ", 2);
	ft_putstr_fd(cmd->cmd[0], 2);
	ft_putstr_fd("\n", 2);
	bin_path = NULL;
	ret_val = find_binary(env, cmd, bin_path, path);
	if (ret_val == 127)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putstr_fd(cmd->cmd[0], 2);
		ft_putstr_fd("\n", 2);
		free_paths(path);
	}
	return (ret_val);
}

int	find_binary(t_data *env, t_simple_cmd *cmd, char *bin_path, char **path)
{
	struct stat	file;
	int			i;
	int			ret;

	i = -1;
	while (path && path[++i])
	{
		bin_path = concat_path(path[i], cmd->cmd[0]);
		ft_putstr_fd("Checking path: ", 2);
		ft_putstr_fd(bin_path, 2);
		ft_putstr_fd("\n", 2);
		if (lstat(bin_path, &file) != -1)
		{
			if (check_permission(file))
			{
				ret = execute_path(bin_path, env, cmd);
				free_paths(path);
				return (ret);
			}
			free(bin_path);
		}
		else
			free(bin_path);
	}
	return (127);
}

static void	handle_exec_error(char *mess)
{
	ft_putstr_fd(mess, 2);
	exit(EXIT_FAILURE);
}

int	execute_path(char *bin_path, t_data *env, t_simple_cmd *cmd)
{
	pid_t	pid;
	int		result;

	pid = fork();
	result = 0;
	if (pid == 0)
	{
		result = execve(bin_path, cmd->cmd, env->env_var);
		if (result == -1)
			handle_exec_error("execve failed\n");
	}
	else if (pid < 0)
	{
		free(bin_path);
		ft_putstr_fd("Fork failed", 2);
		return (-1);
	}
	cmd->pid = pid;
	waitpid(pid, &result, 0);
	free(bin_path);
	env->last_result = WEXITSTATUS(result);
	return (env->last_result);
}

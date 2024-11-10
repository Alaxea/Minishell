/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:15:43 by astefans          #+#    #+#             */
/*   Updated: 2024/11/10 16:08:06 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	search_in_path(t_data *env, t_simple_cmd *cmd)
{
	char	*bin_path;
	char	**path;
	char	*tmp;
	int		ret_val;
	int		i;

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
		i = 0;
		while (path[i])
			free(path[i++]);
		free(path);
	}
	return (ret_val);
}

int	find_binary(t_data *env, t_simple_cmd *cmd, char *bin_path, char **path)
{
	struct stat	file;
	int			i;
	int			ret;
	int			j;

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
				j = 0;
				while (path[j])
					free(path[j++]);
				free(path);
				return (ret);
			}
			free(bin_path);
		}
		else
			free(bin_path);
	}
	return (127);
}

int	execute_path(char *bin_path, t_data *env, t_simple_cmd *cmd)
{
	pid_t	pid;
	int		result;
	char	**argv;

	pid = fork();
	argv = NULL;
	result = 0;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (pid == 0)
	{
		argv = cmd->cmd;
		result = execve(bin_path, argv, env->env_var);
		if (result == -1)
		{
			ft_putstr_fd("execve failed", 2);
			exit(EXIT_FAILURE);
		}
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

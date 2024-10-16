/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:15:43 by astefans          #+#    #+#             */
/*   Updated: 2024/10/16 20:32:51 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	search_in_path(t_data *env, t_simple_cmd com)
{
	char		*bin_path;
	char		**path;
	char		*tmp;
	int			ret_val;

	if (com.cmd && (com.cmd[0][0] == '.' || com.cmd[0][0] == '/'))
	{
		bin_path = find_script(com.cmd[0], env);
		return (execute_path(bin_path, env, &com));
	}
	tmp = set_env_var(env, "PATH");
	if (!tmp)
		return (127);
	path = ft_split(tmp, ':');
	free(tmp);
	bin_path = 0;
	ret_val = find_binary(env, com, bin_path, path);
	if (ret_val == 127)
	{
		ft_putstr_fd("Unrecognized command\n", 2);
		free(path);
	}
	return (ret_val);
}

int	find_binary(t_data *env, t_simple_cmd com, char *bin_path, char **path)
{
	struct stat	file;
	int			i;

	i = -1;
	while (path && path[++i])
	{
		bin_path = concat_path(path[i], com.cmd[0]);
		if (lstat(bin_path, &file) != -1)
		{
			free(path);
			if (check_permission(file))
				return (execute_path(bin_path, env, &com));
		}
		else
			free(bin_path);
	}
	return (127);
}

int	execute_path(char *bin_path, t_data *env, t_simple_cmd *com)
{
	pid_t pid;
	int		result;
	char	**argv;

	pid = fork();
	argv = NULL;
	result = 0;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (pid == 0)
	{
		argv = com->arguments;
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
	com->pid = pid;
	waitpid(pid, &result, 0);
	free(bin_path);
	env->last_result = WEXITSTATUS(result);
	return (env->last_result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:15:43 by astefans          #+#    #+#             */
/*   Updated: 2024/09/23 12:15:53 by astefans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	pc_search_in_path(t_data *env, t_simple_cmd com)
{
	char		*bin_path;
	char		**path;
	char		*tmp;
	int			ret_val;

	if (com.command[0] == '.' || com.command[0] == '/')
	{
		bin_path = find_script(com.command, env);
		return (execute_path(bin_path, env, com));
	}
	tmp = get_env_var(env, "PATH");
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

int	pc_find_binary(t_data *env, t_simple_cmd com, char *bin_path, char **path)
{
	struct stat	file;
	int			i;

	i = -1;
	while (path && path[++i])
	{
		bin_path = concat_path(path[i], com.command);
		if (lstat(bin_path, &file) != -1)
		{
			free(path);
			if (check_permision(file))
				return (execute_path(bin_path, env, com));
		}
		else
			free(bin_path);
	}
	return (127);
}

int	pc_execute_path(char *bin_path, t_data *env, t_simple_cmd com)
{
	pid_t	pid;
	int		result;
	char	**argv;

	pid = fork();
	argv = 0;
	result = 0;
	//signal handle
	if (pid == 0)
	{
		argv = change_command_to_argv(com);
		result = execve(bin_path, argv, env->env_var);
	}
	else if (pid < 0)
	{
		free(bin_path);
		ft_putstr_fd("Fork failed", 2);
		return (-1);
	}
	wait(&result);
	free(bin_path);
	free(argv);
	env->last_result = result;
	return (result);
}

char	**change_command_to_argv(t_simple_cmd com) //to execve()
{
	char	**argv;
	int i;
	int j;

	i = 0;
	while(com.arguments[i])
		i++;
	argv = malloc(sizeof(char *) * (i + 3));
	i = 0;
	argv[i] = ft_strdup(com.command);
	if (com.flags)
		argv[++i] = ft_strjoin("-", com.flags);
	j = 0;
	if (com.arguments)
	{
		while (com.arguments[j])
			argv[++i] = ft_strdup(com.arguments[j++]);		
	}
	argv[++i] = 0;
	return (argv);
}
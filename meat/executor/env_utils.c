/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:06:17 by astefans          #+#    #+#             */
/*   Updated: 2024/11/15 23:30:18 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	copy_env_var(t_data *env, char **env_var)
{
	int	i;
	int	size;

	size = 0;
	while (env_var[size])
		size++;
	env->env_var = (char **)malloc(sizeof(char *) * (size + 1));
	if (!env->env_var)
		return ;
	i = 0;
	while (env_var[i])
	{
		env->env_var[i] = ft_strdup(env_var[i]);
		i++;
	}
	env->env_var[i] = NULL;
}

char	*set_env_var(t_data *env, char *name)
{
	int		i;
	size_t	temp;

	i = 0;
	while (env->env_var[i])
	{
		temp = ft_strchrn(env->env_var[i], '=');
		if (ft_strncmp(env->env_var[i], name, ft_strlen(name)) == 0
			&& temp == ft_strlen(name))
			return (ft_strdup(env->env_var[i] + temp + 1));
		i++;
	}
	return (NULL);
}

static char	**create_new_env(t_data *env, char *temp)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env->env_var[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env->env_var[i])
	{
		new_env[i] = ft_strdup(env->env_var[i]);
		if (!new_env[i])
		{
			while (i > 0)
				free(new_env[--i]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = temp;
	new_env[i + 1] = NULL;
	return (new_env);
}

void	add_env_var(t_data *env, char *name, char *value)
{
	char	*new_var;
	char	*temp;
	char	**new_env;

	if (!env || !name || !value)
		return ;
	new_var = ft_strjoin(name, "=");
	if (!new_var)
		return ;
	temp = ft_strjoin(new_var, value);
	free(new_var);
	if (!temp)
		return ;
	delete_env_var(env, name);
	new_env = create_new_env(env, temp);
	if (!new_env)
	{
		free(temp);
		return ;
	}
	clear_tab(env->env_var);
	env->env_var = new_env;
	env->envp = new_env;
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

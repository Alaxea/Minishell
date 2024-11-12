/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:06:17 by astefans          #+#    #+#             */
/*   Updated: 2024/11/12 17:18:30 by alicja           ###   ########.fr       */
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

/*static char	*join_env_var(char *name, char *value)
{
	char	*new_var;
	char	*temp;

	new_var = ft_strjoin(name, "=");
	if (!new_var)
		return (NULL);
	temp = ft_strjoin(new_var, value);
	free(new_var);
	return (temp);
}

static char	**allocate_new_env(t_data *env, int new_size)
{
	char	**new_env;
	int		i;

	new_env = malloc(sizeof(char *) * new_size);
	if (!new_env)
		return (NULL);
	i = 0;
	while (env->env_var[i])
	{
		new_env[i] = ft_strdup(env->env_var[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

void	add_env_var(t_data *env, char *name, char *value)
{
	char	*temp;
	char	**new_env;
	int		i;

	if (!env || !name || !value)
		return ;
	temp = join_env_var(name, value);
	if (!temp)
		return ;
	delete_env_var(env, name);
	new_env = allocate_new_env(env, i + 2);
	if (!new_env)
	{
		free(temp);
		return ;
	}
	new_env[i] = temp;
	clear_tab(env->env_var);
	env->env_var = new_env;
	env->envp = new_env;
}

static char	**allocate_new_env_for_delete(t_data *env, int var_count)
{
	char	**new_env;

	new_env = malloc(sizeof(char *) * var_count);
	if (!new_env)
		return (NULL);
	return (new_env);
}

static void	copy_env_without_var(t_data *env, char **new_env,
		char *name, int var_count)
{
	int	i;
	int	j;
	int	name_len;

	i = 0;
	j = 0;
	name_len = ft_strlen(name);
	while (env->env_var[i])
	{
		if (ft_strncmp(env->env_var[i], name, name_len) != 0
			|| (env->env_var[i][name_len]
			&& env->env_var[i][name_len] != '='))
		{
			new_env[j] = ft_strdup(env->env_var[i]);
			if (!new_env[j])
			{
				while (--j >= 0)
					free(new_env[j]);
				free(new_env);
				return ;
			}
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
}

void	delete_env_var(t_data *env, char *name)
{
	int		var_count;
	char	**new_env;

	if (!env || !env->env_var || !name)
		return ;
	var_count = 0;
	while (env->env_var[var_count])
		var_count++;
	new_env = allocate_new_env_for_delete(env, var_count);
	if (!new_env)
		return ;
	copy_env_without_var(env, new_env, name, var_count);
	clear_tab(env->env_var);
	env->env_var = new_env;
	env->envp = new_env;
}*/

void	add_env_var(t_data *env, char *name, char *value)
{
	char	*new_var;
	char	*temp;
	int		i;
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
	i = 0;
	while (env->env_var[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
	{
		free(temp);
		return ;
	}
	i = 0;
	while (env->env_var[i])
	{
		new_env[i] = ft_strdup(env->env_var[i]);
		i++;
	}
	new_env[i] = temp;
	new_env[i + 1] = NULL;
	clear_tab(env->env_var);
	env->env_var = new_env;
	env->envp = new_env;
}

void	delete_env_var(t_data *env, char *name)
{
	int		var_count;
	int		name_len;
	int		i;
	int		j;
	char	**new_env;

	if (!env || !env->env_var || !name)
		return ;
	var_count = 0;
	name_len = ft_strlen(name);
	while (env->env_var[var_count])
		var_count++;
	new_env = malloc(sizeof(char *) * (var_count + 1));
	if (!new_env)
		return ;
	i = 0;
	j = 0;
	while (env->env_var[i])
	{
		if (ft_strncmp(env->env_var[i], name, name_len) != 0
			|| (env->env_var[i][name_len] && env->env_var[i][name_len] != '='))
		{
			new_env[j] = ft_strdup(env->env_var[i]);
			if (!new_env[j])
			{
				while (--j >= 0)
					free(new_env[j]);
				free(new_env);
				return ;
			}
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	i = 0;
	while (env->env_var[i])
	{
		free(env->env_var[i]);
		i++;
	}
	free(env->env_var);
	env->env_var = new_env;
	env->envp = new_env;
}

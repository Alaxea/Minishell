/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:06:17 by astefans          #+#    #+#             */
/*   Updated: 2024/11/08 14:29:27 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*create_env_entry(char *name, char *value)
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

static int	get_env_size(char **env_var)
{
	int	i;

	i = 0;
	while (env_var[i])
		i++;
	return (i);
}

static char **allocate_env_array(int size)
	return (malloc(sizeof(char *) * (size + 1)));

static void	copy_env_vars(char **src, char **dst)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = ft_strdup(src[i]);
		i++;
	}
	dst[i] = NULL;
}

static void	update_env(t_data *env, char **new_env)
{
	clear_tab(env->env_var);
	env->env_var = new_env;
	env->envp = new_env;
}

void	add_env_var(t_data *env, char *name, char *value)
{
	char	*temp;
	char	**new_env;
	int		env_size;

	if (!env || !name || !value)
		return ;
	temp = create_env_entry(name, value);
	if (!temp)
		return ;
	delete_env_var(env, name);
	env_size = get_env_size(env->env_var);
	new_env = allocate_env_array(env_size + 1);
	if (!new_env)
	{
		free(temp);
		return ;
	}
	copy_env_vars(env->env_var, new_env);
	new_env[env_size] = temp;
	new_env[env_size + 1] = NULL;
	update_env(env, new_env);
}

static void	remove_env_entry(t_data *env, char *name,
			int name_len, char **new_env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env->env_var[i])
	{
		if (!is_matching_var(env->env_var[i], name, name_len))
		{
			new_env[j] = ft_strdup(env->env_var[i]);
			if (!new_env[j])
			{
				free_env_array(new_env, j);
				return ;
			}
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	free_env_array(env->env_var, get_env_size(env->env_var));
}

static int	is_matching_var(char *env_entry, char *name, int name_len)
{
	return (ft_strncmp(env_entry, name, name_len) == 0
		&& (!env_entry[name_len] || env_entry[name_len] == '='));
}

static void	free_env_array(char **env_var, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (env_var[i])
			free(env_var[i]);
		i++;
	}
	free(env_var);
}

void	delete_env_var(t_data *env, char *name)
{
	char	**new_env;
	int		name_len;
	int		var_count;

	if (!env || !env->env_var || !name)
		return ;
	var_count = get_env_size(env->env_var);
	new_env = allocate_env_array(var_count);
	if (!new_env)
		return ;
	name_len = ft_strlen(name);
	remove_env_entry(env, name, name_len, new_env);
	update_env(env, new_env);
}

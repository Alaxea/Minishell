/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:06:17 by astefans          #+#    #+#             */
/*   Updated: 2024/11/20 23:38:40 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	**allocate_new_env(int var_count)
{
	char	**new_env;

	new_env = malloc(sizeof(char *) * (var_count + 1));
	if (!new_env)
		return (NULL);
	return (new_env);
}

static int	copy_env_except(char **new_env, char **env_var,
			const char *name, size_t name_len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env_var[i])
	{
		if (ft_strncmp(env_var[i], name, name_len) != 0
			|| (env_var[i][name_len] && env_var[i][name_len] != '='))
		{
			new_env[j] = ft_strdup(env_var[i]);
			if (!new_env[j])
			{
				while (--j >= 0)
					free(new_env[j]);
				return (1);
			}
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	return (0);
}

static void	free_old_env(char **env_var)
{
	int	i;

	i = 0;
	while (env_var[i])
	{
		free(env_var[i]);
		i++;
	}
	free(env_var);
}

void	delete_env_var(t_data *env, char *name)
{
	int		var_count;
	int		name_len;
	char	**new_env;

	if (!env || !env->env_var || !name)
		return ;
	name_len = ft_strlen(name);
	var_count = 0;
	while (env->env_var[var_count])
		var_count++;
	new_env = allocate_new_env(var_count);
	if (!new_env)
		return ;
	if (copy_env_except(new_env, env->env_var, name, name_len))
	{
		free(new_env);
		return ;
	}
	free_old_env(env->env_var);
	env->env_var = new_env;
	env->envp = new_env;
}

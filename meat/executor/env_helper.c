/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:06:17 by astefans          #+#    #+#             */
/*   Updated: 2024/11/15 15:52:00 by alicja           ###   ########.fr       */
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

/*void	add_env_var(t_data *env, char *name, char *value)
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
}*/

static char    **create_new_env(t_data *env, char *temp)
{
    int     i;
    char    **new_env;

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

void    add_env_var(t_data *env, char *name, char *value)
{
    char    *new_var;
    char    *temp;
    char    **new_env;

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

static char	**allocate_new_env(int var_count)
{
	char	**new_env;

	new_env = malloc(sizeof(char *) * (var_count + 1));
	if (!new_env)
		return (NULL);
	return (new_env);
}

static int	copy_env_except(char **new_env, char **env_var, const char *name, size_t name_len)
{
	int	i = 0;
	int	j = 0;

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
	int	i = 0;

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

/*void	delete_env_var(t_data *env, char *name)
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
}*/

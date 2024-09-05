/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:06:17 by astefans          #+#    #+#             */
/*   Updated: 2024/09/05 13:03:29 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	copy_env_var(t_data *env, char **env_var)
{
	int i;
	int size;

	size = 0;
	while(env_var[size])
		size++;
	env->env_var = (char **)malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (env_var[i])
	{
		env->env_var[i] = ft_strdup(env_var[i]);
		i++;
	}
	env->env_var[i] = 0;
}

char	*get_env_var(t_data *env, char *name)
{
	int i;
	size_t temp;

	i = 0;
	while (env->env_var[i])
	{
		temp = ft_strchrn(env->env_var[i], '=');
		if (ft_strncmp(env->env_var[i], name, ft_strlen(name)) == 0
			&& temp == ft_strlen(name))
				return (ft_strdup(env->env_var[i] + temp + 1));
		i++;
	}
	return (0);
}

void	add_env_var(t_data *env, char *name, char *value)
{
	int i;
	int size;
	char **res;
	char *temp;

	size = 0;
	while (env->env_var[size])
		size++;
	res = (char **)malloc(sizeof(char *) * (size + 2));
	i = 0;
	while (env->env_var[i])
	{
		res[i] = ft_strdup(env->env_var[i]);
		i++;
	}
	temp = ft_strjoin(name, "=");
	res[i] = ft_strjoin(temp, value);
	free(temp);
	res[++i] = 0;
	clear_tab(env->env_var);
	env->env_var = res;
}

void	delete_env_var(t_data *env, char *name)
{
	int i;
	int j;
	int size;
	char **res;
	int tmp;

	size = 0;
	while (env->env_var[size])
		size++;
	res = (char **)malloc(sizeof(char *) * (size + 1));
	i = 0;
	j = 0;
	while (env->env_var[i])
	{
		tmp = ft_strchrn(env->env_var[i], '=');
		if (ft_strncmp(env->env_var[i], name, ft_strlen(name)) == 0
			&& (size_t)tmp == ft_strlen(name))
			continue ;
		res[j] = ft_strdup(env->env_var[i]);
		j++;
	}
	res[j] = 0;
	clear_tab(env->env_var);
	env->env_var = res;
}
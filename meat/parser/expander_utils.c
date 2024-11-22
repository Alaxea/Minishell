/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:25:09 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/11/22 10:58:18 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	replace_with_exit_status(t_simple_cmd *sc, t_data *data)
{
	int	i;

	i = 1;
	while (sc->cmd[i])
	{
		if (ft_strcmp(sc->cmd[i], "$?") == 0)
		{
			free(sc->cmd[i]);
			sc->cmd[i] = ft_itoa(data->last_result);
		}
		i++;
	}
}

char	*find_env_var(char *str, int *start, int *stop)
{
	*start = 0;
	while (str[*start] != '$' && str[*start])
		(*start)++;
	(*start)++;
	*stop = *start;
	while (str[*stop] && str[*stop] != ' ' && str[*stop] != '"')
		(*stop)++;
	return (ft_substr(str, *start, *stop - *start));
}

char	*trim_quotes(char *command)
{
	bool	trim;
	char	*copy;

	trim = false;
	copy = NULL;
	if (command[0] == '\'' && command[ft_strlen(command) - 1] == '\'')
		trim = true;
	else if (command[0] == '\"' && command[ft_strlen(command) - 1] == '\"')
		trim = true;
	if (trim)
	{
		copy = ft_substr(command, 1, ft_strlen(command) - 2);
		free(command);
		return (copy);
	}
	else
		return (command);
}

size_t	ft_len_until_eq_sign(char *env)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=')
	{
		i++;
	}
	return (i);
}

char	*get_env(char **env, char *var)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(var, env[i], ft_len_until_eq_sign(env[i])) == 0)
			return (ft_strjoin("",
					(env[i] + ft_len_until_eq_sign(env[i]) + 1)));
		else
			i++;
	}
	return (ft_strdup(""));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:49:58 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/09/20 16:57:19 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


char	*find_env(char **env, char *var)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(var, env[i], ft_strlen(var)) == 0)
			return (ft_strjoin("", (env[i] + ft_strlen(var) + 1)));
		else
			i++;
	}
	return (NULL);
}

void	check_quote_str(t_quote_mode *mode, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		check_quote(mode, str[i]);
		i++;
	}
}

char	*double_quotes_env(char *str, char **env)
{
	int	start = 0;
	int	stop;
	char	*var;
	char	*env_expanded;
	char	*b;
	char	*e;
	char	*first;
	char	*sec;

	while (str[start] != '$' && str[start])
		start++;
	start++;
	stop = start;
	while (str[stop] && str[stop] != ' ' && str[stop] != '"')
		stop++;
	var = ft_substr(str, start, stop - start);
	env_expanded = find_env(env, var);
	b = ft_substr(str, 0, start - 1);
	first = ft_strjoin(b, env_expanded);
	free(var);
	if (str[ft_strlen(str) - stop])
	{
		e = ft_substr(str, stop, ft_strlen(str) - stop);
		sec = ft_strjoin(first, e);
	}
	else
		return (first);
	return (sec);
}

char *replace_env(char *str, char **env)
{
	int	start;
	int	stop;
	char	*var;
	char	*env_expanded;
	t_quote_mode	mode;

	start = 0;
	mode = DEFAULT;
	check_quote(&mode, str[0]);
	if (mode == SINGLE_Q)
		return (str);
	if (mode == DOUBLE_Q)
		return (double_quotes_env(str, env));
	while (str[start] != '$' && str[start])
		start++;
	start++;
	stop = start;
	while (str[stop])
		stop++;
	var = ft_substr(str, start, stop);
	free(str);
	env_expanded = find_env(env, var);
	free(var);
	return (env_expanded);
}


void	expand_cmd(int i, t_simple_cmd *sc_node, char **env)
{
	if (i == 0)
	{
		sc_node->cmd[i] = replace_env(sc_node->cmd[i], env);
		sc_node->name = sc_node->cmd[i];
	}
	else
		sc_node->cmd[i] = replace_env(sc_node->cmd[i], env);
}

int	expand(t_simple_cmd *cmds, char **env)
{
	int	i;
	t_simple_cmd *buf;
	char 	*found;

	buf = cmds;
	while (buf)
	{
		i = 0;
		while (buf->cmd[i])
		{
			found = NULL;
			found = ft_strchr(buf->cmd[i], '$');
			if (found)
			{
				expand_cmd(i, buf, env);
				if (buf->cmd[i][0] == '\"')
					i--;
			}
			buf->cmd[i] = trim_quotes(buf->cmd[i]);	
			i++;
		}
		buf = buf->next;
	}
	return (1);
}

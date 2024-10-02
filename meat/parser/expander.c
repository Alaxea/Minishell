/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:49:58 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/10/02 14:33:43 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


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
	int		stop;
	int		start;
	char	*var;
	char	*env_expanded;
	char	*b;
	char	*e;
	char	*first;
	char	*sec;

	var = find_env_var(str, &start, &stop);
	env_expanded = get_env(env, var);
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
	env_expanded = get_env(env, var);
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

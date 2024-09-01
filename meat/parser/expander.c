/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:49:58 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/09/01 13:54:42 by zogorzeb         ###   ########.fr       */
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

// void	check_quote(t_quote_mode *mode, char c)
// {
// 	if (*mode == DEFAULT)
// 	{
// 		if (c == '\'')
// 			*mode = SINGLE_Q;
// 		else if (c == '\"')
// 			*mode = DOUBLE_Q;
// 	}
// 	else if (*mode == SINGLE_Q && c == '\'')
// 		*mode = DEFAULT;
// 	else if (*mode == DOUBLE_Q && c == '\"')
// 		*mode = DEFAULT;
// }

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
	printf("variable %s\n", var);
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
	printf("%s\n", sec);
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
	printf("%s\n", str);
	check_quote(&mode, str[0]);
	if (mode == SINGLE_Q)
		return (str);
	if (mode == DOUBLE_Q)
	{
		printf("double\n");
		return (double_quotes_env(str, env));
	}
	printf("normal\n");
	while (str[start] != '$' && str[start])
		start++;
	start++;
	stop = start;
	while (str[stop])
		stop++;
	var = ft_substr(str, start, stop);
	free(str);
	printf("variable %s\n", var);
	env_expanded = find_env(env, var);
	free(var);
	printf("%s\n", env_expanded);
	return (env_expanded);
}


void	expand_cmd(int i, t_simple_cmd *sc_node, char **env)
{
	if (i == 0)
	{
		sc_node->cmd[i] = replace_env(sc_node->cmd[i], env);
		printf("cmd[0]: %s\n", sc_node->cmd[i]);
		sc_node->name = sc_node->cmd[i];
		printf("name: %s\n", sc_node->cmd[i]);

	}
	else
	{
		sc_node->cmd[i] = replace_env(sc_node->cmd[i], env);
		printf("cmd[%d]: %s\n", i, sc_node->cmd[i]);

	}
}
int	expand(t_simple_cmd **cmds, char **env)
{
	int	i;
	t_simple_cmd *buf;
	char	*found;

	i = 0;
	buf = *cmds;
	while (buf)
	{
		i = 0;
		while (buf->cmd[i])
		{
			found = ft_strnstr(buf->cmd[i], "$", ft_strlen(buf->cmd[i]));
			if (found)
			{
				printf("found\n");
				expand_cmd(i, buf, env);
			}
			i++;
		}
		buf = buf->next;
	}
	return (0);
}


// int main(int argc, char **argv, char **env)
// {
// 	(void)argc;
// 	char *str = double_quotes_env(argv[1], env);
// 	printf("%s\n", str);
// 	return (0);
// }

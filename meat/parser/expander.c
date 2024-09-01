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

char *replace_env(char *str, char **env)
{
	int	start;
	int	stop;
	char	*var;
	char	*env_expanded;

	start = 0;
	printf("%s\n", str);
	while (str[start] != '$' && str[start])
		start++;
	start++;
	stop = start;
	while (str[stop] != ' ' && str[stop])
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
// 	// printf("%s\n", replace_env(argv[1], env));
// 	replace_env(argv[1], env);
// 	return (0);
// }
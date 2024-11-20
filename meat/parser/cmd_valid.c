/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 14:09:00 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/11/20 15:45:07 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
	1. ściezka do komendy
		a) czy jest to sciezka absolutna? jesli tak, zostaw oryginalną
		b) czy zaczyna sie od "./"? jesli tak, zmien na absolutna 
			przy uzyciu funkcji getcwd albo env.var.PWD
*/

int	is_cmd_valid(t_simple_cmd *cmds, char **env)
{
	char	*str;

	while (cmds)
	{
		if (access(cmds->name, F_OK | X_OK) == -1)
		{
			str = get_full_path(cmds->name, env);
			if (str == NULL)
			{
				printf("minishell: %s: command not found\n", cmds->name);
				return (0);
			}
			free(str);
		}
		cmds = cmds->next;
	}
	return (1);
}

void	path_expander(t_simple_cmd *cmds, char **env)
{
	char	*str1;
	char	*str2;
	char	*str3;

	while (cmds)
	{
		if (cmds->name[0] == '.' && cmds->name[1] == '/')
		{
			str1 = ft_substr(cmds->name, 2, ft_strlen(cmds->name) - 2);
			str2 = ft_strjoin(get_env(env, "PWD"), "/");
			str3 = ft_strjoin(str2, str1);
			free(str2);
			free(cmds->cmd[0]);
			cmds->cmd[0] = str1;
			cmds->name = str3;
		}
		cmds = cmds->next;
	}
}

int	cmd_validation(t_simple_cmd *cmds, char **env)
{
	path_expander(cmds, env);
	if (!check_for_builtins(cmds))
	{
		if (!is_cmd_valid(cmds, env))
		{
			free_simple_cmd(cmds);
			return (0);
		}
	}
	return (1);
}

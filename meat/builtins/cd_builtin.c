/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:16:20 by astefans          #+#    #+#             */
/*   Updated: 2024/11/05 17:34:36 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int		cd_helper(t_simple_cmd *cmd, char *cwd);

int		cd_builtin(t_data *env, t_simple_cmd *cmd)
{
	char *home;
	char buffer[1024];
	int ret_val;

	home = set_env_var(env, "HOME");
	ret_val = cd_helper(cmd, home);
	delete_env_var(env, "PWD");
	add_env_var(env, "PWD", getcwd(buffer, 1024));
	return (ret_val);
}

static int		cd_helper(t_simple_cmd *cmd, char *cwd)
{
	if (cmd->cmd[0] == NULL)
	{
		if (cwd == NULL)
		{
			ft_putstr_fd("The HOME variable is not set\n", 2);
			return (1);
		}
		if (chdir(cwd) != 0)
		{
			ft_putstr_fd("The HOME variable is not valid\n", 2);
			return (1);
		}
	}
	else
	{
		if (chdir(cmd->cmd[0]) != 0)
		{
			ft_putstr_fd("cd: No such file or directory\n", 2);
			return (1);
		}
	}
	return (0);
}
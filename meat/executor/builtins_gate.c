/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_gate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:18:20 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/11/22 11:20:44 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	clean_builtin(t_data *data)
{
	t_simple_cmd	*next;

	while (data->simple_cmds)
	{
		next = data->simple_cmds->next;
		free_simple_cmd(data->simple_cmds);
		data->simple_cmds = next;
	}
	if (data->env_var)
		clear_tab(data->env_var);
}

int	execute_builtin(t_data *data, t_simple_cmd *cmd)
{
	int	ret;

	if (ft_strcmp(cmd->name, "pwd") == 0)
		return (pwd_builtin(data, cmd));
	if (ft_strcmp(cmd->name, "echo") == 0)
	{
		ret = echo_builtin(cmd);
		return (ret);
	}
	if (ft_strcmp(cmd->name, "cd") == 0)
		return (cd_builtin(data, cmd));
	if (ft_strcmp(cmd->name, "env") == 0)
		return (env_builtin(data, cmd));
	if (ft_strcmp(cmd->name, "export") == 0)
		return (export_builtin(data, cmd));
	if (ft_strcmp(cmd->name, "exit") == 0)
		return (exit_builtin(data, cmd));
	if (ft_strcmp(cmd->name, "unset") == 0)
		return (unset_builtin(data, cmd));
	return (0);
}

int	check_for_builtins(t_simple_cmd *sc)
{
	int	is_builtin;

	if (!sc->name)
		return (0);
	is_builtin = (ft_strcmp(sc->name, "pwd") == 0
			|| ft_strcmp(sc->name, "echo") == 0
			|| ft_strcmp(sc->name, "cd") == 0
			|| ft_strcmp(sc->name, "env") == 0
			|| ft_strcmp(sc->name, "export") == 0
			|| ft_strcmp(sc->name, "exit") == 0
			|| ft_strcmp(sc->name, "unset") == 0);
	return (is_builtin);
}

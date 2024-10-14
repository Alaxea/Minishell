/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_gate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:18:20 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/10/14 20:36:11 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*int	execute_builtin(t_data *data)
{
	if (ft_strcmp(data->simple_cmds->name, "pwd") == 0)
		return (pwd_builtin(data, data->simple_cmds));
	if (ft_strcmp(data->simple_cmds->name, "echo") == 0)
		return (echo_builtin(data->simple_cmds));
	if (ft_strcmp(data->simple_cmds->name, "cd") == 0)
		return (cd_builtin(data, *data->simple_cmds));
	if (ft_strcmp(data->simple_cmds->name, "env") == 0)
		return (env_builtin(data, *data->simple_cmds));
	if (ft_strcmp(data->simple_cmds->name, "export") == 0)
		return (export_builtin(data, *data->simple_cmds));
	if (ft_strcmp(data->simple_cmds->name, "exit") == 0)
		return (exit_builtin(data, *data->simple_cmds));
	if (ft_strcmp(data->simple_cmds->name, "unset") == 0)
		 return (unset_builtin(data, *data->simple_cmds));
	return (0);
}*/

int	execute_builtin(t_data *data, t_simple_cmd *cmd)
{
	if (ft_strcmp(cmd->name, "pwd") == 0)
		return (pwd_builtin(data, cmd));
    if (ft_strcmp(cmd->name, "echo") == 0)
        return (echo_builtin(cmd));
    if (ft_strcmp(cmd->name, "cd") == 0)
        return (cd_builtin(data, *cmd));
    if (ft_strcmp(cmd->name, "env") == 0)
        return (env_builtin(data, cmd));
    if (ft_strcmp(cmd->name, "export") == 0)
        return (export_builtin(data, *cmd));
    if (ft_strcmp(cmd->name, "exit") == 0)
        return (exit_builtin(data, *cmd));
    if (ft_strcmp(cmd->name, "unset") == 0)
	{
        return (unset_builtin(data, *cmd));
	}
	return (0);
}

int	check_for_builtins(t_simple_cmd *sc)
{
	if (!sc->name)
		return (0);
	if ((ft_strcmp(sc->name, "pwd") == 0)
		|| (ft_strcmp(sc->name, "echo") == 0)
		|| (ft_strcmp(sc->name, "cd") == 0)
		|| (ft_strcmp(sc->name, "env") == 0)
		|| (ft_strcmp(sc->name, "export") == 0)
		|| (ft_strcmp(sc->name, "exit") == 0)
		|| (ft_strcmp(sc->name, "unset") == 0))
		return (1);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_gate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:18:20 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/11/06 11:41:04 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int execute_builtin(t_data *data, t_simple_cmd *cmd)
{
	if (ft_strcmp(cmd->name, "pwd") == 0)
		return (pwd_builtin(data, cmd));
	if (ft_strcmp(cmd->name, "echo") == 0)
	{
		int ret = echo_builtin(cmd);
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

int check_for_builtins(t_simple_cmd *sc)
{
    int is_builtin;

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

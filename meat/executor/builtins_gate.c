/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_gate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:18:20 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/09/05 15:43:56 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	execute_builtin(t_data *data)
{
	if (ft_strcmp(data->simple_cmds->name, "pwd") == 0)
		pwd_builtin(data);
	else if (ft_strcmp(data->simple_cmds->name, "echo") == 0)
		echo_builtin(*data->simple_cmds);
	else if (ft_strcmp(data->simple_cmds->name, "cd") == 0)
		cd_builtin(data, *data->simple_cmds);
	else if (ft_strcmp(data->simple_cmds->name, "env") == 0)
		env_builtin(data);
	else if (ft_strcmp(data->simple_cmds->name, "export") == 0)
		return (1);
	else if (ft_strcmp(data->simple_cmds->name, "exit") == 0)
		exit_builtin(data, *data->simple_cmds);
	else if (ft_strcmp(data->simple_cmds->name, "unset") == 0)
		 return (1);
	return (0);
}

int	check_for_builtins(t_simple_cmd *sc)
{
	if (ft_strcmp(sc->name, "pwd") == 0)
		return (1);
	else if (ft_strcmp(sc->name, "echo") == 0)
		return (1);
	else if (ft_strcmp(sc->name, "cd") == 0)
		return (1);
	else if (ft_strcmp(sc->name, "env") == 0)
		return (1);
	else if (ft_strcmp(sc->name, "export") == 0)
		return (1);
	else if (ft_strcmp(sc->name, "exit") == 0)
		return (1);
	else if (ft_strcmp(sc->name, "unset") == 0)
		return (1);
	else
		return (0);
}
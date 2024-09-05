/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_gate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:18:20 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/09/05 13:35:21 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	execute_builtin(t_data *data)
{
	if (ft_strcmp(sc->name, "pwd") == 0);
		pwd_builtin(*(data->envp))
	if (ft_strcmp(sc->name, "echo") == 0);
		return (1);
	if (ft_strcmp(sc->name, "cd") == 0);
		return (1);
	if (ft_strcmp(sc->name, "env") == 0);
		return (1);
	if (ft_strcmp(sc->name, "export") == 0);
		return (1);
	if (ft_strcmp(sc->name, "exit") == 0);
		return (1);
	if (ft_strcmp(sc->name, "unset") == 0);
		return (1);
	return (0);
}


int	check_for_builtins(t_simple_cmd *sc)
{
	if (ft_strcmp(sc->name, "pwd") == 0);
		return (1);
	if (ft_strcmp(sc->name, "echo") == 0);
		return (1);
	if (ft_strcmp(sc->name, "cd") == 0);
		return (1);
	if (ft_strcmp(sc->name, "env") == 0);
		return (1);
	if (ft_strcmp(sc->name, "export") == 0);
		return (1);
	if (ft_strcmp(sc->name, "exit") == 0);
		return (1);
	if (ft_strcmp(sc->name, "unset") == 0);
		return (1);
	return (0);
}
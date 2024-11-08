/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:17:34 by astefans          #+#    #+#             */
/*   Updated: 2024/11/08 08:54:56 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_valid_identifier(const char *str)
{
	if (!str || !*str || ft_isdigit(*str))
		return (0);
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

static void	print_unset_error(char *var_name)
{
	ft_putstr_fd("unset: `", 2);
	ft_putstr_fd(var_name, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

static int	unset_variable(t_data *env, char *var_name)
{
	if (var_name[0] == '$')
		var_name++;
	if (!is_valid_identifier(var_name))
	{
		print_unset_error(var_name);
		return (1);
	}
	delete_env_var(env, var_name);
	return (0);
}

int	unset_builtin(t_data *env, t_simple_cmd *cmd)
{
	int		i;
	int		status;

	if (!cmd->cmd[1])
	{
		ft_putstr_fd("unset: not enough arguments\n", 2);
		return (1);
	}
	i = 1;
	status = 0;
	while (cmd->cmd[i])
	{
		if (unset_variable(env, cmd->cmd[i]) == 1)
			status = 1;
		i++;
	}
	return (status);
}

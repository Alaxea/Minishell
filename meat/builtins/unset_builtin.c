/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:17:34 by astefans          #+#    #+#             */
/*   Updated: 2024/10/17 23:05:47 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		unset_builtin(t_data *env, t_simple_cmd *cmd)
{
	char *temp;
	
	if (!cmd->cmd[1]) 
	{
		ft_putstr_fd("unset: not enough arguments\n", 2);
		return (1);
	}
	if (ft_strchr(cmd->cmd[1], '='))
	{
		ft_putstr_fd("unset: invalid argument\n", 2);
		return (1);
	}
	temp = ft_strdup(cmd->cmd[1]);
	if (!temp)
		return (1); 
	delete_env_var(env, temp);
	free(temp);
	return (0);
}
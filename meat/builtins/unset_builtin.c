/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:17:34 by astefans          #+#    #+#             */
/*   Updated: 2024/11/05 17:32:44 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int is_valid_identifier(const char *str)
{
    if (!str || !*str || ft_isdigit(*str))
        return 0;

    while (*str) 
	{
        if (!ft_isalnum(*str) && *str != '_')
            return 0;
        str++;
    }
    return 1;
}

int unset_builtin(t_data *env, t_simple_cmd *cmd)
{
    if (!cmd->cmd[1]) 
	{
        ft_putstr_fd("unset: not enough arguments\n", 2);
        return 1;
    }

    int i = 1;
    int status = 0;

    while (cmd->cmd[i]) 
	{
        char *var_name = cmd->cmd[i];

        // Skip if variable name starts with $
        if (var_name[0] == '$')
            var_name++;

        if (!is_valid_identifier(var_name)) 
		{
            ft_putstr_fd("unset: `", 2);
            ft_putstr_fd(var_name, 2);
            ft_putstr_fd("': not a valid identifier\n", 2);
            status = 1;
            i++;
            continue;
        }
        delete_env_var(env, var_name);
        i++;
    }
    return status;
}
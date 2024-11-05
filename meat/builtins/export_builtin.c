/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:17:08 by astefans          #+#    #+#             */
/*   Updated: 2024/11/05 17:33:12 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int export_builtin(t_data *env, t_simple_cmd *cmd)
{
    if (!cmd || !cmd->cmd)
        return (1);

    if (!cmd->cmd[1])
    {
        print_tab(env->envp, STDOUT_FILENO);
        return (0);
    }
    int i = 1;
    while (cmd->cmd[i])
    {
        char *var = cmd->cmd[i];
        char *equals_pos = ft_strchr(var, '=');

        if (!equals_pos)
        {
            i++;
            continue;
        }
        int name_len = equals_pos - var;
        char *name = ft_substr(var, 0, name_len);
        char *value = equals_pos + 1;
        // Remove quotes if present
        if (value[0] == '"' && value[ft_strlen(value)-1] == '"') 
        {
            value++;
            value[ft_strlen(value)-1] = '\0';
        }
        add_env_var(env, name, value);
        free(name);
        i++;
    }
    return (0);
}
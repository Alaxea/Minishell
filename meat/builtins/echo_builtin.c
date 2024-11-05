/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:21:26 by astefans          #+#    #+#             */
/*   Updated: 2024/11/05 17:34:28 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int echo_builtin(t_simple_cmd *cmd)
{
    int i = 1;
    while (cmd->cmd[i])
    {
        write(STDOUT_FILENO, cmd->cmd[i], ft_strlen(cmd->cmd[i]));
        if (cmd->cmd[i + 1])
            write(STDOUT_FILENO, " ", 1);
        i++;
    }
    write(STDOUT_FILENO, "\n", 1);
    return 0;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:34:01 by astefans          #+#    #+#             */
/*   Updated: 2024/11/05 17:32:47 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int pwd_builtin(t_data *data, t_simple_cmd *cmd)
{
    char *pwd;

    (void)data; // Silence unused parameter warning
    (void)cmd;  // We don't need cmd->fd_out anymore

    pwd = getcwd(NULL, 0);
    if (!pwd)
    {
        ft_putstr_fd("pwd: error retrieving current directory\n", 2);
        return (1);
    }
    ft_putstr_fd(pwd, STDOUT_FILENO);
    ft_putstr_fd("\n", STDOUT_FILENO);
    free(pwd);
    return (0);
}
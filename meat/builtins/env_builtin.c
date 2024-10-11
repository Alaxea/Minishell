/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:15:58 by astefans          #+#    #+#             */
/*   Updated: 2024/10/11 16:23:34 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_tab(char **tab)
{
	int i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}

int		env_builtin(t_data *data, t_simple_cmd *cmd)
{
	int i;

	redir_builtin(cmd);
	i = 0;
	while (data->envp[i])
	{
		ft_putstr_fd(data->envp[i], cmd->fd_out);
		ft_putstr_fd("\n", cmd->fd_out);
		i++;
	}
	return(0);
}
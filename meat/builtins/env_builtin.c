/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:15:58 by astefans          #+#    #+#             */
/*   Updated: 2024/11/05 17:33:46 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_tab(char **tab, int fd_out)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		ft_putstr_fd(tab[i], fd_out);
		ft_putstr_fd("\n", fd_out);
		i++;
	}
}

int	env_builtin(t_data *data, t_simple_cmd *cmd)
{
	if (!data || !data->envp || !cmd)
		return (-1);
	(void)cmd;
	print_tab(data->envp, STDOUT_FILENO);
	return (0);
}

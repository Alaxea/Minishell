/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:15:58 by astefans          #+#    #+#             */
/*   Updated: 2024/10/16 22:10:31 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_tab(char **tab, int fd_out)
{
	int i;

	if (!tab)
		return;
	i = 0;
	while (tab[i])
	{
		ft_putstr_fd(tab[i], fd_out);
        ft_putstr_fd("\n", fd_out); 
		i++;
	}
}

int		env_builtin(t_data *data, t_simple_cmd *cmd)
{

	if (!data || !data->envp || !cmd) // Sprawdzenie, czy wskaźniki są prawidłowe
        return (-1);
	redir_builtin(cmd);
	if (cmd->fd_out < 0)
    {
        ft_putstr_fd("Error with output file descriptor\n", 2);
        return -1; // Zwracamy błąd, jeśli fd_out jest nieprawidłowy
    }
    print_tab(data->envp, cmd->fd_out);
	return(0);
}
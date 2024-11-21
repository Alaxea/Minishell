/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:02:18 by astefans          #+#    #+#             */
/*   Updated: 2024/11/21 20:06:49 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argv;
	(void)argc;
	ft_memset(&data, 0, sizeof(t_data));
	copy_env_var(&data, envp);
	if (!data.env_var)
		return (1);
	data.envp = data.env_var;
	minishell(&data);
	if (data.env_var)
		clear_tab(data.env_var);
	return (0);
}

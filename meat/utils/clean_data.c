/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:01:07 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/11/22 11:10:36 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	clean_data(t_data *data)
{
	t_simple_cmd	*next;

	while (data->simple_cmds)
	{
		next = data->simple_cmds->next;
		free_simple_cmd(data->simple_cmds);
		data->simple_cmds = next;
	}
	data->simple_cmds = NULL;
	free(data->input);
	data->input = NULL;
}

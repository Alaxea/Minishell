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

int		unset_builtin(t_data *env, t_simple_cmd com)
{
	char	*temp;
	int		temp2;

	if (!com.cmd[0])
		return (1);
	temp2 = ft_strchrn(com.cmd[1], '=');
	if (!temp2)
		return (1);
	temp = ft_substr(com.cmd[1], 0, temp2);
	delete_env_var(env, temp);
	free (temp);
	return (0);
}
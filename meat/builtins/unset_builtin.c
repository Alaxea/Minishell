/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:17:34 by astefans          #+#    #+#             */
/*   Updated: 2024/08/26 14:17:36 by astefans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		unset_builtin(t_data *env, t_simple_cmd com)
{
	char	*temp;
	int		temp2;

	if (!com.arguments[0] || com.arguments[1])
		return (1);
	temp2 = ft_strchrn(com.arguments[0], '=');
	if (!temp2)
		return (1);
	temp = ft_substr(com.arguments[0], 0, temp2);
	delete_env_var(env, temp);
	free (temp);
	return (0);
}
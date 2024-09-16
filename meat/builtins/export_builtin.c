/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:17:08 by astefans          #+#    #+#             */
/*   Updated: 2024/08/26 14:17:09 by astefans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		export_builtin(t_data *env, t_simple_cmd com)
{
	char	*temp;
	char	*temp2;
	int		temp3;

	if (!com.arguments[0] || com.arguments[1])
		return (1);
	temp3 = ft_strchrn(com.arguments[0], '=');
	if (!temp3)
		return (1);
	temp = ft_substr(com.arguments[0], 0, temp3);
	delete_env_var(env, temp);
	temp2 = ft_substr(com.arguments[0], temp3 + 1,
			ft_strlen(com.arguments[0] - ft_strlen(temp) - 1));
	add_env_var(env, temp, temp2);
	free(temp);
	free(temp2);
	return (0);
}
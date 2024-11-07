/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:17:08 by astefans          #+#    #+#             */
/*   Updated: 2024/11/05 17:33:12 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	export_builtin(t_data *env, t_simple_cmd *cmd)
{
	int		i;
	char	*var;
	char	*equals_pos;
	char	*name;
	char	*value;
	int		name_len;

	if (!cmd || !cmd->cmd)
		return (1);
	if (!cmd->cmd[1])
	{
		print_tab(env->envp, STDOUT_FILENO);
		return (0);
	}
	i = 1;
	while (cmd->cmd[i])
	{
		var = cmd->cmd[i];
		equals_pos = ft_strchr(var, '=');
		if (!equals_pos)
		{
			i++;
			continue ;
		}
		name_len = equals_pos - var;
		name = ft_substr(var, 0, name_len);
		value = equals_pos + 1;
		if (value[0] == '"' && value[ft_strlen(value) - 1] == '"')
		{
			value++;
			value[ft_strlen(value) - 1] = '\0';
		}
		add_env_var(env, name, value);
		free(name);
		i++;
	}
	return (0);
}

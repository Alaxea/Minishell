/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:17:08 by astefans          #+#    #+#             */
/*   Updated: 2024/11/08 09:14:52 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*extract_name(const char *var, int name_len)
{
	return (ft_substr(var, 0, name_len));
}

static char	*extract_value(char *equals_pos)
{
	char	*value;

	value = equals_pos + 1;
	if (value[0] == '"' && value[ft_strlen(value) - 1] == '"')
	{
		value++;
		value[ft_strlen(value) - 1] = '\0';
	}
	return (value);
}

static int	process_var(t_data *env, char *var)
{
	char	*equals_pos;
	char	*name;
	char	*value;
	int		name_len;

	equals_pos = ft_strchr(var, '=');
	if (!equals_pos)
		return (1);
	name_len = equals_pos - var;
	name = extract_name(var, name_len);
	value = extract_value(equals_pos);
	if (!name || !value)
	{
		free(name);
		return (1);
	}
	add_env_var(env, name, value);
	free(name);
	return (0);
}

int	export_builtin(t_data *env, t_simple_cmd *cmd)
{
	int		i;

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
		process_var(env, cmd->cmd[i]);
		i++;
	}
	return (0);
}

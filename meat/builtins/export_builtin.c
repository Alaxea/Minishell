/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:17:08 by astefans          #+#    #+#             */
/*   Updated: 2024/10/17 23:44:01 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_valid_env_var(const char *key_value)
{
	int i;

	if (!key_value || key_value[0] == '=' || ft_isdigit(key_value[0]))
		return (0);
	i = 0;
	while (key_value[i] && key_value[i] != '=')
	{
		if (!ft_isalnum(key_value[i]) && key_value[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
int export_builtin(t_data *env, t_simple_cmd *cmd)
{
    char *name;
    char *value;
    int equal_pos;

    if (!cmd->cmd[1])
    {
        ft_putstr_fd("minishell: export: Invalid arguments\n", STDERR_FILENO);
        return (EXIT_FAILURE);
    }
    equal_pos = ft_strchrn(cmd->cmd[1], '=');
    if (equal_pos == -1)
    {
        ft_putstr_fd("minishell: export: `", STDERR_FILENO);
        ft_putstr_fd(cmd->cmd[1], STDERR_FILENO);
        ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
        return (EXIT_FAILURE);
    }
    name = ft_substr(cmd->cmd[1], 0, equal_pos);
    value = ft_substr(cmd->cmd[1], equal_pos + 1, ft_strlen(cmd->cmd[1]) - equal_pos - 1);
    if (!name || !value)
    {
        free(name);
        free(value);
        ft_putstr_fd("Memory allocation error\n", STDERR_FILENO);
        return (EXIT_FAILURE);
    }
    if (!is_valid_env_var(name))
    {
        free(name);
        free(value);
        ft_putstr_fd("minishell: export: `", STDERR_FILENO);
        ft_putstr_fd(name, STDERR_FILENO);
        ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
        return (EXIT_FAILURE);
    }
    add_env_var(env, name, value);
    free(name);
    free(value);
    ft_putstr_fd("Export completed\n", STDOUT_FILENO);
    return (EXIT_SUCCESS);
}

/*int		export_builtin(t_data *env, t_simple_cmd *cmd)
{
	char	*temp; //do nazwy zmiennej
	char	*temp2; //do wartości zmiennej
	int		temp3;

	printf("Before checking args\n");
	if (!cmd->cmd[1])
	{
		ft_putstr_fd("export: Invalid arguments\n", 2);
		return (1);
	}
	printf("Before strchrn\n");
	temp3 = ft_strchrn(cmd->cmd[1], '=');
	printf("After strchrn: %d\n", temp3);
	if (temp3 == -1)
	{
		ft_putstr_fd("export: Invalid format\n", 2);
		return (1);
	}
	printf("Before extracting variable name\n");
	temp = ft_substr(cmd->cmd[1], 0, temp3);
	if (!temp)
    {
        ft_putstr_fd("Memory allocation error\n", 2);
        return (1);
    }
	printf("Variable name: %s\n", temp);
	if (set_env_var(env, temp) != NULL)
    {
        delete_env_var(env, temp);
    }
	printf("Before extracting variable value\n");
	temp2 = ft_substr(cmd->cmd[1], temp3 + 1,
			ft_strlen(cmd->cmd[1]) - temp3 - 1);
	if (!temp2)
    {
		free(temp);
        ft_putstr_fd("Memory allocation error\n", 2);
        return (1);
    }
	printf("Variable value: %s\n", temp2);
	add_env_var(env, temp, temp2);
	//free(temp);
	//free(temp2);
	printf("Export completed\n");
	return (0);
}*/
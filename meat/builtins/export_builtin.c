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

int		export_builtin(t_data *env, t_simple_cmd *cmd)
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
}
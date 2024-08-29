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

static char **get_key_value(char *arg)
{
	char	**temp;
	char	*equals_pos;

	equals_pos = ft_strchr(arg, '=');
	temp = malloc(sizeof * temp * (2 + 1));
	temp[0] = ft_substr(arg, 0, equals_pos - arg);
	temp[1] = ft_substr(equals_pos, 1, ft_strlen(equals_pos));
	temp[2] = NULL;
	return (temp);
}

int		export_builtin(t_data *data, char **args)
{
	int		i;
	int		ex_code;
	char	**temp;

	ex_code = EXIT_SUCCESS;
	i = 1;
	if (!args[i])
		return (env_builtin(data, NULL));
	while (args[i])
	{
		if(!is_valid_env_var_key(args[i]))
		{
			perror("Error");
			ex_code = EXIT_FAILURE;
		}
		else if (ft_strchr(args[i], '=') != NULL)
		{
			temp = get_key_value(args[i]);
			free(temp);
		}
		i++;
	}
	return(ex_code);
}

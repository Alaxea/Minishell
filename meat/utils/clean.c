/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:09:57 by astefans          #+#    #+#             */
/*   Updated: 2024/11/06 11:56:41 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	clear_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			tab[i] = NULL;
			i++;
		}
		free(tab);
		tab = NULL;
	}
}

void	clear_env(t_data *env)
{
	if (!env)
		return ;
	if (env->env_var)
	{
		clear_tab(env->env_var);
		env->env_var = NULL;
	}
	if (env->envp)
	{
		clear_tab(env->envp);
		env->envp = NULL;
	}
}

void	exit_shell(t_data *env, char *mess, int fail)
{
	(void)mess;
	if (!env)
	{
		if (fail)
			exit(fail);
		exit(EXIT_SUCCESS);
	}
	clear_env(env);
	if (fail == -1)
		exit(EXIT_FAILURE);
	else if (!fail)
		exit(EXIT_SUCCESS);
	else
		exit(fail);
}

void	free_simple_cmd(t_simple_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	if (cmd->cmd)
	{
		while (cmd->cmd[i])
		{
			free(cmd->cmd[i]);
			i++;
		}
		free(cmd->cmd);
	}
	if (cmd->delimiter_heredoc)
		free(cmd->delimiter_heredoc);
	if (cmd->input_path)
		free(cmd->input_path);
	if (cmd->output_path)
		free(cmd->output_path);
	if (cmd->output_path_append)
		free(cmd->output_path_append);
	if (cmd->path)
		free(cmd->path);
	free(cmd);
}

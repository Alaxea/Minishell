/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:09:57 by astefans          #+#    #+#             */
/*   Updated: 2024/11/21 19:54:00 by zogorzeb         ###   ########.fr       */
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

void	free_simple_cmd(t_simple_cmd *sc)
{
	int	i;

	i = 0;
	while (sc->cmd[i])
	{
		free(sc->cmd[i]);
		sc->cmd[i] = NULL;
		i++;
	}
	free(sc->cmd);
	if (sc->delimiter_heredoc)
		free(sc->delimiter_heredoc);
	if (sc->input_path)
		free(sc->input_path);
	if (sc->output_path)
		free(sc->output_path);
	if (sc->output_path_append)
		free(sc->output_path_append);
	if (sc->path)
		free(sc->path);
	free(sc);
}

void	free_paths(char **paths)
{
	int		i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

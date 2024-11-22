/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:02:18 by astefans          #+#    #+#             */
/*   Updated: 2024/11/22 11:54:42 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	restore_std(int saved_stdout, int saved_stdin)
{
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
	if (saved_stdin != -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
}

static int	execute_builtin_cmd(t_data *data, t_simple_cmd *current)
{
	int	saved_stdout;
	int	saved_stdin;
	int	ret;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	if (redir_check(current) == -1)
		return (1);
	ret = execute_builtin(data, current);
	restore_std(saved_stdout, saved_stdin);
	return (ret);
}

int	executing(t_data *data)
{
	t_simple_cmd	*current;
	int				ret;

	if (!data || !data->simple_cmds)
		return (1);
	current = data->simple_cmds;
	ret = 0;
	if (check_for_builtins(current) && !current->next)
		ret = execute_builtin_cmd(data, current);
	else
		ret = execute(current, data);
	if (ret != 0)
		return (ret);
	return (ret);
}

int	parsing(t_data *data)
{
	if (data->input)
	{
		data->tokens = token_creator(data->input, 0, 0);
		if (!data->tokens)
			return (0);
		if (!validation(&data->tokens))
			return (0);
		data->simple_cmds = parser(data->tokens);
		ft_lstclear(&data->tokens);
		if (!data->simple_cmds)
			return (0);
		if (!expand(data->simple_cmds, data->envp, data))
			return (0);
		if (!cmd_validation(data, data->simple_cmds, data->envp))
			return (0);
	}
	return (1);
}

int	minishell(t_data *data)
{
	while (1)
	{
		setup_signals();
		data->input = readline("minishell>> ");
		if (!data->input)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (ft_strcmp(data->input, "") == 0)
		{
			free(data->input);
			continue ;
		}
		add_history(data->input);
		if (parsing(data))
		{
			data->last_result = executing(data);
			clean_data(data);
		}
	}
	return (0);
}

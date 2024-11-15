/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:02:18 by astefans          #+#    #+#             */
/*   Updated: 2024/11/16 00:06:07 by alicja           ###   ########.fr       */
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
	while (current && current->name)
	{
		if (check_for_builtins(current) && !current->next)
			ret = execute_builtin_cmd(data, current);
		else
			ret = execute(current, data);
		if (ret != 0)
			return (ret);
		break ;
	}
	return (ret);
}

int	parsing(t_data *data)
{
	if (data->input)
	{
		data->tokens = token_creator(data->input);
		if (!data->tokens)
			return (0);
		if (!validation(&data->tokens))
			return (0);
		data->simple_cmds = parser(data->tokens);
		if (!data->simple_cmds)
			return (0);
		if (!expand(data->simple_cmds, data->envp, data))
			return (0);
		if (!cmd_validation(data->simple_cmds, data->envp))
			return (0);
	}
	return (1);
}

int	minishell(t_data *data)
{
	t_simple_cmd	*current;
	t_simple_cmd	*next;

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
			if (data->tokens)
				ft_lstclear(&data->tokens);
			if (data->simple_cmds)
			{
				current = data->simple_cmds;
				while (current)
				{
					next = current->next;
					free_simple_cmd(current);
					current = next;
				}
				data->simple_cmds = NULL;
			}
		}
		free(data->input);
		data->input = NULL;
	}
	return (0);
}

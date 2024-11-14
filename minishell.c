/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:02:18 by astefans          #+#    #+#             */
/*   Updated: 2024/11/14 12:33:01 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executing(t_data *data)
{
	t_simple_cmd	*current;
	int				ret;
	int				saved_stdout;
	int				saved_stdin;

	if (!data || !data->simple_cmds)
		return (1);
	current = data->simple_cmds;
	ret = 0;
	while (current && current->name)
	{
		if (check_for_builtins(current) && !current->next)
		{
			saved_stdout = dup(STDOUT_FILENO);
			saved_stdin = dup(STDIN_FILENO);
			if (redir_check(current) == -1)
				return (1);
			ret = execute_builtin(data, current);
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
			if (ret != 0)
				return (ret);
		}
		else
		{
			ret = execute(current, data);
			if (ret != 0)
				return (ret);
		}
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
	int				ret;
	t_simple_cmd	*current;
	t_simple_cmd	*next;

	while (1)
	{
		// signals();
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
			ret = executing(data);
			data->last_result = ret;
			if (ret != 0)
				printf("Executing returned with error: %d\n", ret);
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

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argv;
	(void)argc;
	ft_memset(&data, 0, sizeof(t_data));
	copy_env_var(&data, envp);
	if (!data.env_var)
		return (1);
	data.envp = data.env_var;
	minishell(&data);
	if (data.env_var)
		clear_tab(data.env_var);
	return (0);
}

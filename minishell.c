#include "minishell.h"
/*command to compilation: cc -Wall -Wextra -Werror -o main main.c -lreadline*/


int	executing(t_data *data)
{
	if (check_for_builtins(data->simple_cmds))
		execute_builtin(data);
	else
		//pipex();
	return (0);
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
		if (!expand(data->simple_cmds, data->envp))
			return (0);
		if (!cmd_validation(data->simple_cmds, data->envp))
			return (0);
	}
	return (1);
}

int	minishell(t_data *data)
{
	//tutaj sygnały//
	while(1)
	{
		/*if (data->input == NULL)
		{
			signal(SIGQUIT, SIG_IGN);
		}*/
		data->input = readline("minishell>> ");
		if (!data->input)
			break ;
		if (ft_strcmp(data->input, "") == 0)
		{
			free(data->input);
			continue ;
		}
		add_history(data->input);
		int flag = parsing(data);
		if (flag != 0)
		{
			redir_check(data->cmd);
			executing(data);
		}
		execute_command(data->cmd, data->envp);
	}
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	t_data	data;
	
	(void)argv;
	(void)argc;
	data.envp = envp;
	data.env_var = envp;
	minishell(&data);
}

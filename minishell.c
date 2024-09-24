#include "minishell.h"
/*command to compilation: cc -Wall -Wextra -Werror -o main main.c -lreadline
I tested it for exit and ls -l and it works*/

int	executing(t_data *data)
{
	//bramka na builtins
	if (check_for_builtins(data->simple_cmds))
		//printf("builtin\n");
		execute_builtin(data);
	// else
	// 	executor();
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
	t_simple_cmd cmd;
	char **commands;

	while(1)
	{
		data->input = readline("minishell>> ");
		if (!data->input)
			break;
		/*if the line is empty, continue to the next iteration*/
		if (ft_strcmp(data->input, "") == 0)
		{
			free(data->input);
			continue;
		}
		/*to add line to the history*/
		add_history(data->input);
		commands = ft_split(data->input, ' ');
		cmd.commands = commands;
		/*if the user types "exit", break the loop and exit*/
		if (!cmd.commands || cmd.commands[0] == 0)
		{
			free(data->input);
			continue;
		}
		execute_command(&cmd, data->envp);
		free(cmd.commands);
		free(data->input);
		/*int flag = parsing(data);
		if (flag != 0)
			executing(data);
		if (data->input)
			free(data->input);
		data->input = NULL;*/
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

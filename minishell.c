#include "minishell.h"
/*command to compilation: cc -Wall -Wextra -Werror -o main main.c -lreadline*/


int	executing(t_data *data)
{
	if (check_for_builtins(data->simple_cmds))
		execute_builtin(data);
	// else
	// 	pipex(data);
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
	signals();
	while(1)
	{
		data->input = readline("minishell>> ");
		if (!data->input)
		{
			printf("exit\n");
			break;
		}
		if (ft_strcmp(data->input, "") == 0)
		{
			free(data->input);
			continue ;
		}
		add_history(data->input);
		int flag = parsing(data);
		if (flag != 0)
		{
			//redir_check();
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



//void	minishell(t_data *env);

/*int main(int argc, char **argv, char **envp)
{
	t_data	data;
	
	(void)argv;
	(void)argc;
	data.envp = envp;
	data.env_var = envp;
	copy_env_var(&data, envp);
	minishell(&data);
	clear_env(&data);
	return(0);
}*/

/*void	minishell(t_data *env)
{
	char		*input;
	t_simple_cmd	*commands;

	while (1)
	{
		signals();
		input = readline("minishell>> ");
		if (input == NULL)
			break ;
		if (!input[0])
			continue ;
		add_history(input);
		env->tokens = token_creator(input);
		commands = parser(env->tokens);
		if (!commands || commands[0].command == 0)
			continue ;
		env->last_result = execute_command(commands, env->envp);
		//pc_free_commands_tab(commands);
		free(input);
	}
}*/
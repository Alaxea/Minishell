#include "minishell.h"
/*command to compilation: cc -Wall -Wextra -Werror -o main main.c -lreadline
I tested it for exit and ls -l and it works*/

int	executing(t_data *data)
{
	//bramka na builtins
	if (check_for_builtins(data->simple_cmds))
	{
		//printf("builtin\n");
		execute_builtin(data);
	}
	// else
	// 	executor();
	return (0);
}

int	parsing(t_data *data)
{
	//printf("przed parsingiem\n");
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
		//printf("przed expanderem\n");
		if (expand(&data->simple_cmds, data->envp) == 0)
			return (0);
	}
	//printf("po parsingu\n");
	return (1);
}
int	minishell(t_data *data)
{
	/*to initialize the history*/
	while(1)
	{
		data->input = readline("minishell>> ");
		if (!data->input)
		{
			printf("exit\n");
			exit(1);
		}
		/*if the line is empty, continue to the next iteration*/
		if (ft_strcmp(data->input, "") == 0)
		{
			free(data->input);
			continue;
		}
		/*to add line to the history*/
		add_history(data->input);
		/*if the user types "exit", break the loop and exit*/
		if (ft_strcmp(data->input, "exit") == 0) 
		{
            free(data->input);
            break;
        }
		int flag = parsing(data);
		if (flag != 0)
			executing(data);
		/* and the WINNER for today is this: execute the command using the system's shell*/
		// int status = system(data->input);
		/*to check if the command execution was successful*/
		// if (status == -1) 
		// {
            // perror("system");
        // }
		/*free the memory allocated by readline*/
		if (data->input)
			free(data->input);
		data->input = NULL;
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

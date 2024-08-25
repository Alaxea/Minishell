/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:36:08 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/08/25 22:03:45 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
lexer is breaking input into tokens (words and operators), tokens will be a linked list because this form
allows us to dynamically add next tokens

During token recognition no substitutions shall be actually performed, 
and the result token shall contain exactly the characters that appear in the input 
*/
t_redir_type	recognise_operator(char *str, int i);

t_token *add_token(char *input, int max, int start, t_redir_type type)
{
	char	*str;
	int		i;

	while (ft_iswhitespace(input[max - 1]))
		max--;
	while (ft_iswhitespace(input[start]))
		start++;
	if ((max - start) <= 0)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (max - start) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (start < max)
	{
		str[i] = input[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (ft_lstnew(str, type));
}

t_redir_type	recognise_operator(char *str, int i)
{
	if (str[i] == '>')
		return (REDIR_OUTPUT);
	else if (str[i] == '<')
		return (REDIR_INPUT);
	else if (str[i] == '|')
		return (PIPE);
	if (str[i] == '<' && str[i - 1] == '<')
		return (REDIR_HEREDOC);
	else if (str[i] == '>' && str[i - 1] == '>')
		return (REDIR_APPEND);
	else if (str[i] == '<')
		return (REDIR_INPUT);
	else
		return (STANDARD);
}

int	ft_iswhitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

void	check_quote(t_quote_mode *mode, char c)
{
	if (*mode == DEFAULT)
	{
		if (c == '\'')
			*mode = SINGLE_Q;
		else if (c == '\"')
			*mode = DOUBLE_Q;
	}
	else if (*mode == SINGLE_Q && c == '\'')
		*mode = DEFAULT;
	else if (*mode == DOUBLE_Q && c == '\"')
		*mode = DEFAULT;
}

t_token	*token_creator(char *input)
{
	int				i;
	int				start;
	t_quote_mode	mode;
	t_token 		*token;
	t_token			*new;
	t_redir_type	type_mode;

	i = 0;
	start = 0;
	mode = DEFAULT;
	token = NULL;
	type_mode = recognise_operator(input, i);
	while (input[i])
	{
		type_mode = recognise_operator(input, i);
		check_quote(&mode, input[i]);
		if (recognise_operator(input, i + 1) != type_mode && mode == DEFAULT && input[i + 1])
		{
			new = add_token(input, i + 1, start, recognise_operator(input, i));
			ft_lstadd_back(&token, new);
			start = i + 1;
		}
		if (input[i + 1] == '\0')
			ft_lstadd_back(&token, add_token(input, i + 1, start, recognise_operator(input, i)));
		i++;
	}
	// t_token *buf = token;
	// while (buf)
	// {
	// 	printf("value: %s\n", buf->value); 
	// 	buf = buf->next;
	// }
	// else
	// 	return (validation(&token));
	return (token);
}

// int main()
// {
// 	while (1)
// 	{
// 		char *input = readline("minishell: ");
// 		token_creator(input);
// 	}

// 	return (0);
// }
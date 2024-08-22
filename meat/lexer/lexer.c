/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:36:08 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/08/21 14:17:22 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
lexer is breaking input into tokens (words and operators), tokens will be a linked list because this form
allows us to dynamically add next tokens

During token recognition no substitutions shall be actually performed, 
and the result token shall contain exactly the characters that appear in the input 
*/

t_token *add_token(char *input, int max, int start, t_type type)
{
	printf("add token\n");
	char	*str;
	int		i;

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

static int	recognise_operator(char c)
{
	if (c == '>')
		return (1);
	else if (c == '<')
		return (1);
	else if (c == '|')
		return (1);
	else
		return (0);

}

t_token	*word_or_operator(char *input, int max, int start)
{
	t_token	*new;

	if (recognise_operator(input[max - 1]))
	{
		printf("oper\n");
		new = add_token(input, max, start, OPERATOR);
	}
	else
	{
		printf("word\n");
		new = add_token(input, max, start, WORD);
	}
	return (new);
}

int	ft_iswhitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == '\0' || c == 32)
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

int	token_creator(char *input)
{
	int				i;
	int				start;
	t_quote_mode	mode;
	t_token 		*token;
	t_token			*new;

	i = 0;
	start = 0;
	mode = DEFAULT;
	token = NULL;
	while (input[i])
	{
		check_quote(&mode, input[i]);
		if (ft_iswhitespace(input[i + 1]) && mode == DEFAULT)
		{
			new = word_or_operator(input, i + 1, start);
			// printf("%s\n", new->value);
			start = i + 2;
			ft_lstadd_back(&token, new);
		}
		i++;
	}
	if (mode == SINGLE_Q || mode == DOUBLE_Q)
	{
		token_error(&token, "error - unclosed quotation marks");
		return (0);
	}
	else
		return (validation(&token));
}

int main()
{
	char *input = readline("minishell: ");
	token_creator(input);

	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:54:59 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/11/20 15:12:25 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*trim_the_value(char *old)
{
	size_t	start;
	char	*new;
	int		len;

	start = 0;
	len = ft_strlen(old);
	while (old[start] && old[start] != ' ')
		start++;
	if (old[start] != ' ')
	{
		free(old);
		return (NULL);
	}
	new = ft_substr(old, start + 1, len - start);
	free(old);
	return (new);
}

char	*cut_out_path(char *value)
{
	int		stop;
	char	*ret;
	int		i;

	stop = 0;
	i = 0;
	while (value[stop] && value[stop] != ' ')
		stop++;
	ret = (char *)malloc(sizeof(char) * (stop + 1));
	if (!ret)
		return (NULL);
	while (i < stop)
	{
		ret[i] = value[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

void	redir_modify(t_token *token, t_simple_cmd *simple_cmd,
	t_redir_type type)
{
	if (type == REDIR_INPUT)
		simple_cmd->input_path = cut_out_path(token->next->value);
	else if (type == REDIR_OUTPUT)
		simple_cmd->output_path = cut_out_path(token->next->value);
	else if (type == REDIR_APPEND)
		simple_cmd->output_path_append = cut_out_path(token->next->value);
	else if (type == REDIR_HEREDOC)
	{
		simple_cmd->delimiter_heredoc = cut_out_path(token->next->value);
		simple_cmd->heredoc = true;
	}
}

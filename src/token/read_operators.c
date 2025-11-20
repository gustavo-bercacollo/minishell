/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_operators.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:26:28 by gbercaco          #+#    #+#             */
/*   Updated: 2025/11/18 19:27:42 by gbercaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token *read_pipe(char **s)
{
	(*s)++;
	return (new_token(ft_strdup("|"), TOK_PIPE));
}

static t_token *read_greater(char **s)
{
	(*s)++;
	if (**s == '>')
	{
		(*s)++;
		return (new_token(ft_strdup(">>"), TOK_REDIR_APPEND));
	}
	return (new_token(ft_strdup(">"), TOK_REDIR_OUT));
}

static t_token *read_less(char **s)
{
	(*s)++;
	if (**s == '<')
	{
		(*s)++;
		return (new_token(ft_strdup("<<"), TOK_HEREDOC));
	}
	return (new_token(ft_strdup("<"), TOK_REDIR_IN));
}

t_token	*read_operator(char **s)
{
	if (**s == '|')
		return (read_pipe(s));
	if (**s == '>')
		return (read_greater(s));
	if (**s == '<')
		return (read_less(s));
	return (NULL);
}


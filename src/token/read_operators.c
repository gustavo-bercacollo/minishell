/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_operators.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:26:28 by gbercaco          #+#    #+#             */
/*   Updated: 2025/12/22 20:07:34 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*safe_new_op(char *value, t_toktype type)
{
	t_token	*tok;

	tok = new_token(value, type);
	if (!tok)
	{
		free(value);
		return (NULL);
	}
	return (tok);
}

static t_token	*read_pipe(char **s)
{
	char	*value;

	(*s)++;
	value = ft_strdup("|");
	if (!value)
		return (NULL);
	return (safe_new_op(value, TOK_PIPE));
}

static t_token	*read_greater(char **s)
{
	char	*value;

	(*s)++;
	if (**s == '>')
	{
		(*s)++;
		value = ft_strdup(">>");
		if (!value)
			return (NULL);
		return (safe_new_op(value, TOK_REDIR_APPEND));
	}
	value = ft_strdup(">");
	if (!value)
		return (NULL);
	return (safe_new_op(value, TOK_REDIR_OUT));
}

static t_token	*read_less(char **s)
{
	char	*value;

	(*s)++;
	if (**s == '<')
	{
		(*s)++;
		value = ft_strdup("<<");
		if (!value)
			return (NULL);
		return (safe_new_op(value, TOK_HEREDOC));
	}
	value = ft_strdup("<");
	if (!value)
		return (NULL);
	return (safe_new_op(value, TOK_REDIR_IN));
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

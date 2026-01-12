/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:33:46 by gbercaco          #+#    #+#             */
/*   Updated: 2026/01/11 23:01:44 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*read_and(char **cmd)
{
	t_token	*tok;

	tok = new_token(ft_strdup("&&"), TOK_AND);
	if (!tok)
		return (NULL);
	*cmd += 2;
	return (tok);
}

t_token	*read_or(char **cmd)
{
	t_token	*tok;

	tok = new_token(ft_strdup("||"), TOK_OR);
	if (!tok)
		return (NULL);
	*cmd += 2;
	return (tok);
}

static t_token	*get_token_type(char **comand)
{
	if (**comand == '&' && *(*comand + 1) == '&')
		return (read_and(comand));
	else if (**comand == '|' && *(*comand + 1) == '|')
		return (read_or(comand));
	else if (**comand == '|' || **comand == '<' || **comand == '>')
		return (read_operator(comand));
	else if (**comand == '"' || **comand == '\'')
		return (read_quotes(comand));
	else
		return (read_word(comand));
}

static void	add_token_to_list(t_token **head, t_token **tail, t_token *tok)
{
	if (!*head)
		*head = tok;
	else
		(*tail)->next = tok;
	*tail = tok;
}

t_token	*tokenize(char *comand)
{
	t_token	*head;
	t_token	*tail;
	t_token	*tok;

	head = NULL;
	tail = NULL;
	while (*comand)
	{
		skip_spaces(&comand);
		if (!*comand)
			break ;
		tok = get_token_type(&comand);
		if (!tok)
		{
			free_tokens(&head);
			return (NULL);
		}
		add_token_to_list(&head, &tail, tok);
	}
	return (head);
}

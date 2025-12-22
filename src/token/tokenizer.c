/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:33:46 by gbercaco          #+#    #+#             */
/*   Updated: 2025/12/22 20:09:34 by klima-do         ###   ########.fr       */
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
		if (*comand == '&' && *(comand + 1) == '&')
			tok = read_and(&comand);
		else if (*comand == '|' && *(comand + 1) == '|')
			tok = read_or(&comand);
		else if (*comand == '|' || *comand == '<' || *comand == '>')
			tok = read_operator(&comand);
		else if (*comand == '"' || *comand == '\'')
			tok = read_quotes(&comand);
		else
			tok = read_word(&comand);
		if (!tok)
		{
			free_tokens(&head);
			return (NULL);
		}
		if (!head)
			head = tok;
		else
			tail->next = tok;
		tail = tok;
	}
	return (head);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:33:46 by gbercaco          #+#    #+#             */
/*   Updated: 2025/11/18 17:58:23 by gbercaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		else if (*comand == '"' || *comand == '\'')
			tok = read_quotes(&comand);
		else if (*comand == '|' || *comand == '<' || *comand == '>')
			tok = read_operator(&comand);
		else
			tok = read_word(&comand);
		if (!head)
			head = tok;
		else
			tail->next = tok;
		tail = tok;
	}
	return (head);
}

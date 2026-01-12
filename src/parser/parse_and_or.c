/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_or.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 16:30:09 by klima-do          #+#    #+#             */
/*   Updated: 2026/01/11 21:37:38 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ast	*create_and_or_node(t_ast *left, t_ast *right, t_toktype op)
{
	if (op == TOK_AND)
		return (new_ast_node(NODE_AND, left, right));
	else
		return (new_ast_node(NODE_OR, left, right));
}

t_ast	*parser_and_or(t_token **tok)
{
	t_ast		*left;
	t_ast		*right;
	t_toktype	op;
	t_token		*op_tok;

	left = parse_pipe(tok);
	if (!left)
		return (NULL);
	while (*tok && ((*tok)->type == TOK_AND || (*tok)->type == TOK_OR))
	{
		op_tok = *tok;
		op = op_tok->type;
		*tok = (*tok)->next;
		free_token(op_tok);
		right = parse_pipe(tok);
		if (!right)
		{
			free_ast(left);
			return (NULL);
		}
		left = create_and_or_node(left, right, op);
	}
	return (left);
}

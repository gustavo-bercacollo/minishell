/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_and_or.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 16:30:09 by klima-do          #+#    #+#             */
/*   Updated: 2025/12/18 16:45:19 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*parser_and_or(t_token **tok)
{
	t_ast	*left;
	t_ast	*right;
	t_toktype	op;

	left = parse_pipe(tok);
	if (!left)
		return (NULL);
	while (*tok && ((*tok)->type == TOK_AND || (*tok)->type == TOK_OR))
	{
		op = (*tok)->type;
		*tok = (*tok)->next;
		right = parse_pipe(tok);
		if (!right)
			return (NULL);
		if (op == TOK_AND)
			left = new_ast_node(NODE_AND, left,right);
		else
			left = new_ast_node(NODE_OR, left,right);
	}
	return (left);
}

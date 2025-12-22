/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:56:59 by klima-do          #+#    #+#             */
/*   Updated: 2025/12/22 20:23:33 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*parse_pipe(t_token **tok)
{
	t_ast		*left;
	t_ast		*right;
	t_command	*cmd;
	t_token		*pipe_tok;

	cmd = parse_cmd(tok);
	if (!cmd)
		return (NULL);
	left = ast_from_cmd(cmd);
	while (*tok && (*tok)->type == TOK_PIPE)
	{
		pipe_tok = *tok;
		*tok = (*tok)->next;
		free_token(pipe_tok);
		cmd = parse_cmd(tok);
		if (!cmd)
		{
			free_ast(left);
			return (NULL);
		}
		right = ast_from_cmd(cmd);
		left = new_ast_node(NODE_PIPE, left, right);
	}
	return (left);
}

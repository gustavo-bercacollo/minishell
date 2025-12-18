/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:56:59 by klima-do          #+#    #+#             */
/*   Updated: 2025/12/18 16:16:15 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast 	*parse_pipe(t_token **tok)
{
	t_ast		*left;
	t_ast		*right;
	t_command	*cmd;

	cmd = parse_cmd(tok);
	if(!cmd)
		return (NULL);

	left = ast_from_cmd(cmd);
	while(*tok && (*tok)->type == TOK_PIPE)
	{
		*tok = (*tok)->next;
		cmd = parse_cmd(tok);
		if (!cmd)
			return (NULL);
		right = ast_from_cmd(cmd);
		left = new_ast_node(NODE_PIPE, left, right);
	}
	return (left);
}
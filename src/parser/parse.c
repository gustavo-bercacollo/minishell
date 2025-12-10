/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 17:50:25 by klima-do          #+#    #+#             */
/*   Updated: 2025/12/08 18:44:06 by gbercaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*parse(t_token *tok)
{
	t_command	*cmd;
	t_command	*head;

	cmd = new_command();
	head = cmd;
	while (tok)
	{
		if (tok->type == TOK_WORD)
			add_arg(cmd, tok);
		else if (tok->type == TOK_REDIR_OUT || tok->type == TOK_REDIR_APPEND)
			set_outfile(&tok, cmd);
		else if (tok->type == TOK_HEREDOC)
			set_heredoc(&tok, cmd);
		else if (tok->type == TOK_REDIR_IN)
			set_infile(&tok, cmd);
		else if (tok->type == TOK_PIPE)
		{
			cmd->next = new_command();
			cmd = cmd->next;
		}
		tok = tok->next;
	}
	return (head);
}

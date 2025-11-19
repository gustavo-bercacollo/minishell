/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 17:50:25 by klima-do          #+#    #+#             */
/*   Updated: 2025/11/19 19:02:24 by gbercaco         ###   ########.fr       */
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
			add_arg(cmd, tok->value);
		else if (tok->type == TOK_REDIR_OUT)
		{
			tok = tok->next;
			if (tok)
				cmd->outfile = ft_strdup(tok->value);
			cmd->append = 0;
		}
		else if (tok->type == TOK_REDIR_APPEND)
		{
			tok = tok->next;
			if (tok)
				cmd->outfile = ft_strdup(tok->value);
			cmd->append = 1;
		}
		else if (tok->type == TOK_REDIR_IN)
		{
			tok = tok->next;
			if (tok)
				cmd->infile = ft_strdup(tok->value);
		}
		else if (tok->type == TOK_HEREDOC)
		{
			tok = tok->next;
			if (tok)
				cmd->infile = ft_strdup(tok->value);
			cmd->heredoc = 1;
		}
		else if (tok->type == TOK_PIPE)
		{
			cmd->next = new_command();
			cmd = cmd->next;
		}
		tok = tok->next;
	}
	return (head);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 17:50:25 by klima-do          #+#    #+#             */
/*   Updated: 2025/12/17 17:07:48 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*parse_cmd(t_token **tok)
{
	t_command	*cmd;

	cmd = new_command();
	while (*tok && (*tok)->type != TOK_AND
			&&(*tok)->type != TOK_OR
			&&(*tok)->type != TOK_PIPE)
	{
		if ((*tok)->type == TOK_WORD)
			add_arg(cmd, tok);
		else if ((*tok)->type == TOK_REDIR_OUT || (*tok)->type == TOK_REDIR_APPEND)
			set_outfile(&tok, cmd);
		else if ((*tok)->type == TOK_HEREDOC)
			set_heredoc(&tok, cmd);
		else if ((*tok)->type == TOK_REDIR_IN)
			set_infile(&tok, cmd);
		*tok = (*tok)->next;
	}
	return (cmd);
}

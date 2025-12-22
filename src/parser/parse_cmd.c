/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 17:47:09 by klima-do          #+#    #+#             */
/*   Updated: 2025/12/22 20:39:22 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*parse_cmd(t_token **tok)
{
	t_command	*cmd;
	t_token 	*tmp;
	int			consumed;

	cmd = new_command();
	consumed = 0;
	while (*tok && (*tok)->type != TOK_AND
		&& (*tok)->type != TOK_OR
		&& (*tok)->type != TOK_PIPE)
	{
		if ((*tok)->type == TOK_WORD)
		{

			tmp = *tok;
			add_arg(cmd, tmp);
			*tok = (*tok)->next;
			free_token(tmp);
			consumed = 1;
		}
		else if ((*tok)->type == TOK_REDIR_OUT
			|| (*tok)->type == TOK_REDIR_APPEND)
		{
			set_outfile(tok, cmd);
			consumed = 1;
		}
		else if ((*tok)->type == TOK_REDIR_IN)
		{
			set_infile(tok, cmd);
			consumed = 1;
		}
		else if ((*tok)->type == TOK_HEREDOC)
		{
			set_heredoc(tok, cmd);
			consumed = 1;
		}
		else
			break ;
	}
	if (!consumed)
	{
		free_command(cmd);
		return (NULL);
	}
	return (cmd);
}

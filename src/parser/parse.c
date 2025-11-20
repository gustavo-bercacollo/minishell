/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 17:50:25 by klima-do          #+#    #+#             */
/*   Updated: 2025/11/20 16:38:17 by gbercaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_outfile(t_token **tok, t_command *cmd)
{
	if ((*tok)->type == TOK_REDIR_OUT)
		cmd->append = 0;
	else
		cmd->append = 1;
	if (!(*tok)->next)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `newline`", 2);
		return ;
	}
	*tok = (*tok)->next;
	if (cmd->outfile)
		free(cmd->outfile);
	cmd->outfile = ft_strdup((*tok)->value);
}

static void	set_infile(t_token **tok, t_command *cmd)
{
	if ((*tok)->type == TOK_HEREDOC)
		cmd->heredoc = 1;
	if (!(*tok)->next)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `newline`", 2);
		return ;
	}
	*tok = (*tok)->next;
	if (cmd->outfile)
		free(cmd->infile);
	cmd->infile = ft_strdup((*tok)->value);
}

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
		else if (tok->type == TOK_REDIR_OUT || tok->type == TOK_REDIR_APPEND)
			set_outfile(&tok, cmd);
		else if (tok->type == TOK_REDIR_IN || tok->type == TOK_HEREDOC)
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

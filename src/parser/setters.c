/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 18:30:50 by gbercaco          #+#    #+#             */
/*   Updated: 2025/12/07 22:14:40 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_outfile(t_token **tok, t_command *cmd)
{
	if ((*tok)->type == TOK_REDIR_OUT)
		cmd->append = 0;
	else
		cmd->append = 1;
	if (!(*tok)->next)
		return (ft_putendl_fd("minishell: syntax error", 2));
	*tok = (*tok)->next;
	if (cmd->outfile)
		free(cmd->outfile);
	cmd->outfile = ft_strdup((*tok)->value);
}

void	set_infile(t_token **tok, t_command *cmd)
{
	if ((*tok)->type == TOK_HEREDOC)
		cmd->heredoc = 1;
	if (!(*tok)->next)
		return (ft_putendl_fd("minishell: syntax error", 2));
	*tok = (*tok)->next;
	if (cmd->infile)
		free(cmd->infile);
	cmd->infile = ft_strdup((*tok)->value);
}

void	sigint_heredoc(int sig)
{
	(void)sig;
	g_interrupted = 1;
	close(STDIN_FILENO);
}

void	restoring_stdin(t_command *cmd, t_heredoc *doc)
{
	if (cmd->heredoc == -1)
	{
		close(doc->fd[0]);
		close(doc->fd[1]);
		dup2(doc->saved_stdin, STDIN_FILENO);
		close(doc->saved_stdin);
		init_signals();
		return ;
	}
}

void	loop_heredoc(t_heredoc *doc)
{
	while (1)
	{
		doc->line = readline("> ");
		if (!doc->line && g_interrupted)
		{
			g_interrupted = 0;
			doc->cmd->heredoc = -1;
			return ;
		}
		if (!doc->line)
			return ;
		if (ft_strcmp(doc->line, doc->delim) == 0)
		{
			free(doc->line);
			return ;
		}
		write(doc->fd[1], doc->line, ft_strlen(doc->line));
		write(doc->fd[1], "\n", 1);
		free(doc->line);
	}
}

void	set_heredoc(t_token **tok, t_command *cmd)
{
	t_heredoc	doc;

	if (!(*tok)->next)
		return (ft_putendl_fd("minishell: syntax error near `newline`", 2));
	(*tok) = (*tok)->next;
	doc.delim = (*tok)->value;
	doc.cmd = cmd;
	pipe(doc.fd);
	doc.saved_stdin = dup(STDIN_FILENO);
	signal(SIGINT, sigint_heredoc);
	loop_heredoc(&doc);
	restoring_stdin(cmd, &doc);
	close(doc.fd[1]);
	dup2(doc.saved_stdin, STDIN_FILENO);
	close(doc.saved_stdin);
	init_signals();
	cmd->heredoc_fd = doc.fd[0];
	cmd->heredoc = 1;
}

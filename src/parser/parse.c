/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 17:50:25 by klima-do          #+#    #+#             */
/*   Updated: 2025/12/03 15:44:23 by gbercaco         ###   ########.fr       */
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
		return (ft_putendl_fd("minishell: syntax error ", 2));
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
		return (ft_putendl_fd("minishell: syntax error", 2));
	*tok = (*tok)->next;
	if (cmd->infile)
		free(cmd->infile);
	cmd->infile = ft_strdup((*tok)->value);
}

static void	set_heredoc(t_token **tok, t_command *cmd)
{
	int		fd[2];
	char	*line;
	char	*delim;

	if (!(*tok)->next)
		return (ft_putendl_fd("minishell: syntax error near `newline`", 2));
	(*tok) = (*tok)->next;
	delim = (*tok)->value;
	pipe(fd);
	while (1)
	{
		line = readline("heredoc> ");
		if (!line || ft_strcmp(line, delim) == 0)
			break ;
		if (line && *line != '\0')
		{
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
		}
		free(line);
	}
	free(line);
	close(fd[1]);
	cmd->heredoc_fd = fd[0];
	cmd->heredoc = 1;
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

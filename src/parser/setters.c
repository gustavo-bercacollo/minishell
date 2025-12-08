/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 18:30:50 by gbercaco          #+#    #+#             */
/*   Updated: 2025/12/07 21:26:49 by klima-do         ###   ########.fr       */
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

void	set_heredoc(t_token **tok, t_command *cmd)
{
	int		fd[2];
	char	*line;
	char	*delim;
	int		saved_stdin;

	if (!(*tok)->next)
		return (ft_putendl_fd("minishell: syntax error near `newline`", 2));
	(*tok) = (*tok)->next;
	delim = (*tok)->value;
	pipe(fd);
	saved_stdin = dup(STDIN_FILENO);
	signal(SIGINT, sigint_heredoc);

	while (1)
	{
		line = readline("> ");
		if (!line && g_interrupted)
		{
			close(fd[1]);
			close(fd[0]);
			dup2(saved_stdin, STDIN_FILENO);
			close(saved_stdin);

			g_interrupted = 0;
			init_signals();
			cmd->heredoc = -1;
			return ;
		}
		if (!line || ft_strcmp(line, delim) == 0)
			break ;
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	free(line);
	close(fd[1]);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	init_signals();
	cmd->heredoc_fd = fd[0];
	cmd->heredoc = 1;
}


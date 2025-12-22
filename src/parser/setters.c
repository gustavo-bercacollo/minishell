/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 18:30:50 by gbercaco          #+#    #+#             */
/*   Updated: 2025/12/22 20:40:43 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_outfile(t_token **tok, t_command *cmd)
{
	t_token	*redir;
	t_token	*file;

	redir = *tok;
	file = redir->next;
	if (!file || file->type != TOK_WORD)
	{
		ft_putendl_fd("minishell: syntax error", 2);
		return ;
	}
	cmd->append = (redir->type == TOK_REDIR_APPEND);
	if (cmd->outfile)
		free(cmd->outfile);
	cmd->outfile = ft_strdup(file->value);
	*tok = file->next;
}

void	set_infile(t_token **tok, t_command *cmd)
{
	t_token	*redir;
	t_token	*file;

	redir = *tok;
	file = redir->next;
	if (!file || file->type != TOK_WORD)
	{
		ft_putendl_fd("minishell: syntax error", 2);
		return ;
	}
	if (cmd->infile)
		free(cmd->infile);
	cmd->infile = ft_strdup(file->value);
	*tok = file->next;
}

void	run_heredoc_child(char *delim, int write_fd)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	while (1)
	{
		line = readline("> ");
		if (!line)
			_exit(0);
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			_exit(0);
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
}

int	create_heredoc(char *delim)
{
	int		fd[2];
	pid_t	pid;
	int		status;
	void	(*old_sigint)(int);

	if (pipe(fd) == -1)
		return (-1);
	old_sigint = signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		close(fd[0]);
		run_heredoc_child(delim, fd[1]);
	}
	close(fd[1]);
	waitpid(pid, &status, 0);
	signal(SIGINT, old_sigint);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(fd[0]);
		return (-1);
	}
	return (fd[0]);
}

void	set_heredoc(t_token **tok, t_command *cmd)
{
	t_token	*redir;
	t_token	*delim;
	t_token	*next;

	redir = *tok;
	delim = redir->next;
	if (!delim || delim->type != TOK_WORD)
	{
		ft_putendl_fd("minishell: syntax error", 2);
		cmd->heredoc = -1;
		return ;
	}
	cmd->heredoc_fd = create_heredoc(delim->value);
	cmd->heredoc = (cmd->heredoc_fd == -1) ? -1 : 1;
	next = delim->next;
	free(redir);
	free(delim->value);
	free(delim);
	*tok = next;
}

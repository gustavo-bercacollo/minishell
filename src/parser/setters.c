/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 18:30:50 by gbercaco          #+#    #+#             */
/*   Updated: 2026/01/11 21:36:46 by klima-do         ###   ########.fr       */
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
	free_token(redir);
	free_token(file);
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
	free_token(redir);
	free_token(file);
}

void	run_heredoc_child(char *delim, int write_fd)
{
	char	*line;

	set_signals_child();
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			_exit(0);
		if (ft_strncmp(line, delim, ft_strlen(delim)) == 0
			&& line[ft_strlen(delim)] == '\n')
		{
			free(line);
			_exit(0);
		}
		write(write_fd, line, ft_strlen(line));
		free(line);
	}
}

int	create_heredoc(char *delim)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (pipe(fd) == -1)
		return (-1);
	set_signals_noninteractive();
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		run_heredoc_child(delim, fd[1]);
	}
	close(fd[1]);
	waitpid(pid, &status, 0);
	set_signals_interactive();
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
	if (cmd->heredoc_fd == -1)
		cmd->heredoc = -1;
	else
		cmd->heredoc = 1;
	next = delim->next;
	*tok = next;
	free_token(redir);
	free_token(delim);
}

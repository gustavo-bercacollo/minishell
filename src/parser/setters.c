/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 18:30:50 by gbercaco          #+#    #+#             */
/*   Updated: 2025/12/10 16:55:30 by gbercaco         ###   ########.fr       */
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

void	run_heredoc_child(char *delim, int write_fd)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	while (1)
	{
		line = readline("> ");
		if (!line)
			exit(0);
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			exit(0);
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

	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		run_heredoc_child(delim, fd[1]);
	}
	close(fd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(fd[0]);
		return (-1);
	}
	return (fd[0]);
}

void	set_heredoc(t_token **tok, t_command *cmd)
{
	*tok = (*tok)->next;
	cmd->heredoc_fd = create_heredoc((*tok)->value);
	if (cmd->heredoc_fd == -1)
		cmd->heredoc = -1;
	else
		cmd->heredoc = 1;
}

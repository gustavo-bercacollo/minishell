/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 20:04:11 by gbercaco          #+#    #+#             */
/*   Updated: 2025/12/03 17:21:25 by gbercaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_outfile(t_command *cmd)
{
	int	fd_out;

	if (cmd->append)
		fd_out = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd_out = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out < 0)
	{
		perror(cmd->outfile);
		exit(1);
	}
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
}

void	handle_infile(t_command *cmd)
{
	int	fd_in;

	fd_in = open(cmd->infile, O_RDONLY);
	if (fd_in < 0)
	{
		perror(cmd->infile);
		exit(1);
	}
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
}

void	handle_heredoc(t_command *cmd)
{
	dup2(cmd->heredoc_fd, STDIN_FILENO);
	close(cmd->heredoc_fd);
}

void	handle_pipe_input(int fd_in)
{
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
}

void	handle_pipe_output(int fd[2])
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
}

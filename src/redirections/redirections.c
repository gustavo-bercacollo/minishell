/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 20:04:11 by gbercaco          #+#    #+#             */
/*   Updated: 2026/01/08 20:41:46 by klima-do         ###   ########.fr       */
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
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
}


// int	apply_redirections(t_command *cmd)
// {
// 	if (cmd->in_fd != STDIN_FILENO)
// 	{
// 		dup2(cmd->in_fd, STDIN_FILENO);
// 		close(cmd->in_fd);
// 	}
// 	if (cmd->out_fd != STDOUT_FILENO)
// 	{
// 		dup2(cmd->out_fd, STDOUT_FILENO);
// 		close(cmd->out_fd);
// 	}
// 	return (0);
// }

int	apply_redirections(t_command *cmd)
{
	if (cmd->heredoc_fd >= 0)
		handle_heredoc(cmd);
	if (cmd->infile)
		handle_infile(cmd);
	if (cmd->outfile)
		handle_outfile(cmd);
	return (0);
}

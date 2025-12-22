/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 20:29:52 by klima-do          #+#    #+#             */
/*   Updated: 2025/12/22 16:28:37 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_left_child(int fd[2], t_shell *ms, t_ast *node)
{
	set_default_signals_for_child();
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	exit(execute_node(ms, node->left));
}

void	handle_right_child(int fd[2], t_shell *ms, t_ast *node)
{
	set_default_signals_for_child();
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	exit(execute_node(ms, node->right));
}

int	execute_pipe(t_shell *ms, t_ast *node)
{
	int		status;
	int		fd[2];
	pid_t	left_pid;
	pid_t	right_pid;

	if (pipe(fd) < 0)
	{
		perror("pipe");
		return (1);
	}
	left_pid = fork();
	if (left_pid == 0)
		handle_left_child(fd, ms, node);
	right_pid = fork();
	if (right_pid == 0)
		handle_right_child(fd, ms, node);
	close(fd[0]);
	close(fd[1]);
	waitpid(left_pid, NULL, 0);
	waitpid(right_pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

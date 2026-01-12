/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 20:29:52 by klima-do          #+#    #+#             */
/*   Updated: 2026/01/11 22:20:12 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_left_child(int fd[2], t_shell *ms, t_ast *node)
{
	set_signals_child();
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	_exit(execute_node(ms, node->left));
}

static void	handle_right_child(int fd[2], t_shell *ms, t_ast *node)
{
	set_signals_child();
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	_exit(execute_node(ms, node->right));
}

static int	create_pipe_and_forks(int fd[2], pid_t *left, pid_t *r)
{
	(void)r;
	if (pipe(fd) < 0)
	{
		perror("pipe");
		set_signals_interactive();
		return (1);
	}
	*left = fork();
	if (*left < 0)
	{
		perror("fork");
		set_signals_interactive();
		return (1);
	}
	return (0);
}

static int	fork_right_child(pid_t *right_pid)
{
	*right_pid = fork();
	if (*right_pid < 0)
	{
		perror("fork");
		set_signals_interactive();
		return (1);
	}
	return (0);
}

int	execute_pipe(t_shell *ms, t_ast *node)
{
	int		status;
	int		fd[2];
	pid_t	left_pid;
	pid_t	right_pid;

	set_signals_noninteractive();
	if (create_pipe_and_forks(fd, &left_pid, &right_pid))
		return (1);
	if (left_pid == 0)
		handle_left_child(fd, ms, node);
	if (fork_right_child(&right_pid))
		return (1);
	if (right_pid == 0)
		handle_right_child(fd, ms, node);
	close(fd[0]);
	close(fd[1]);
	waitpid(left_pid, NULL, 0);
	waitpid(right_pid, &status, 0);
	set_signals_interactive();
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

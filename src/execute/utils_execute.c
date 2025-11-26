/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 16:35:19 by gbercaco          #+#    #+#             */
/*   Updated: 2025/11/25 18:43:21 by gbercaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_child(t_shell *ms, t_command *cmd)
{
	char	*path;

	path = get_path(ms->envp, cmd->argv[0]);
	if (!path)
	{
		printf("minishell: command not found: %s\n", cmd->argv[0]);
		exit(127);
	}
	execve(path, cmd->argv, ms->envp);
	perror("execve");
	exit(1);
}

int	exec_parent(t_shell *ms, pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		ms->last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		ms->last_status = 128 + WTERMSIG(status);
	return (ms->last_status);
}

void	run_child_with_pipe(t_shell *ms, t_command *cmd, int fd_in, int fd[2])
{
	if (fd_in != 0)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (cmd->next)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	execute_single(ms, cmd);
	exit(ms->last_status);
}

void	handle_parent_after_fork(int *fd_in, int fd[2], t_command *cmd,
		t_shell *ms, pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		ms->last_status = WEXITSTATUS(status);
	if (*fd_in != 0)
		close(*fd_in);
	if (cmd->next)
	{
		close(fd[1]);
		*fd_in = fd[0];
	}
}

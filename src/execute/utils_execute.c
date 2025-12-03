/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 16:35:19 by gbercaco          #+#    #+#             */
/*   Updated: 2025/12/03 17:22:41 by gbercaco         ###   ########.fr       */
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

void	run_child(t_shell *ms, t_command *cmd, int fd_in, int fd[2])
{
	if (cmd->heredoc)
		handle_heredoc(cmd);
	else if (fd_in != 0)
		handle_pipe_input(fd_in);
	if (cmd->next)
		handle_pipe_output(fd);
	if (cmd->outfile)
		handle_outfile(cmd);
	if (cmd->infile)
		handle_infile(cmd);
	exec_child(ms, cmd);
}

void	wait_child_and_update_status(pid_t pid, t_shell *ms)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		ms->last_status = WEXITSTATUS(status);
}

void	handle_pipe_parent(int *fd_in, int fd[2], t_command *cmd)
{
	if (*fd_in != 0)
		close(*fd_in);
	if (cmd->next)
	{
		close(fd[1]);
		*fd_in = fd[0];
	}
}

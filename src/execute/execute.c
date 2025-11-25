/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:53:53 by klima-do          #+#    #+#             */
/*   Updated: 2025/11/25 18:42:22 by gbercaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_single(t_shell *ms, t_command *cmd)
{
	pid_t	pid;

	if (!cmd->argv || !cmd->argv[0])
		return (0);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
		exec_child(ms, cmd);
	return (exec_parent(ms, pid));
}

int	execute_pipe(t_shell *ms, t_command *cmd)
{
	int		fd[2];
	pid_t	pid;
	int		fd_in;

	fd_in = 0;
	while (cmd)
	{
		if (cmd->next)
			pipe(fd);
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			return (1);
		}
		else if (pid == 0)
			run_child_with_pipe(ms, cmd, fd_in, fd);
		else
			handle_parent_after_fork(&fd_in, fd, cmd, ms, pid);
		cmd = cmd->next;
	}
	return (ms->last_status);
}

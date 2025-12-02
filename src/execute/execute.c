/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:53:53 by klima-do          #+#    #+#             */
/*   Updated: 2025/12/02 19:44:35 by gbercaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(t_shell *ms, t_command *cmd)
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
			return (perror("fork"), 1);
		else if (pid == 0)
			run_child(ms, cmd, fd_in, fd);
		else
			handle_parent(&fd_in, fd, cmd, ms, pid);
		cmd = cmd->next;
	}
	return (ms->last_status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 15:46:14 by gbercaco          #+#    #+#             */
/*   Updated: 2025/12/05 19:20:35 by gbercaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_child_and_update_status(pid_t pid, t_shell *ms)
{
	int	status;
	int	sig;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		ms->last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			write(1, "\n", 1);
		else if (sig == SIGQUIT)
			write(1, "\n", 8);
		ms->last_status = 128 + sig;
	}
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

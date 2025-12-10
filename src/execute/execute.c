/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:53:53 by klima-do          #+#    #+#             */
/*   Updated: 2025/12/05 17:58:24 by gbercaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(t_shell *ms, t_command *cmd)
{
	int			fd[2];
	int			fd_in = 0;
	pid_t		pids[1024];
	int			i = 0;
	int			status;
	t_command	*current = cmd;
	t_command	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->heredoc == -1)
		{
			ms->last_status = 130;
			return (130);
		}
		tmp = tmp->next;
	}
	signal(SIGINT, SIG_IGN);
	while (current)
	{
		if (current->next && pipe(fd) == -1)
			return (perror("pipe"), 1);
		pids[i] = fork();
		if (pids[i] < 0)
			return (perror("fork"), 1);
		if (pids[i] == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			run_child(ms, current, fd_in, fd);
		}
		else
		{
			if (fd_in != 0)
				close(fd_in);
			if (current->next)
			{
				close(fd[1]);
				fd_in = fd[0];
			}
			i++;
		}
		current = current->next;
	}
	int	j;

	j = 0;
	while (j < i)
	{
		waitpid(pids[j], &status, 0);
		if (WIFEXITED(status))
			ms->last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			ms->last_status = 128 + WTERMSIG(status);
		j++;
	}
	signal(SIGINT, sigint_handler);
	return (ms->last_status);
}
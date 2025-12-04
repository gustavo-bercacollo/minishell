/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 15:45:47 by gbercaco          #+#    #+#             */
/*   Updated: 2025/12/04 15:51:51 by gbercaco         ###   ########.fr       */
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
	// if (is_builtin(cmd->argv[0]))
	// {
	// 	execute_builtin(ms, cmd);
	// 	exit(ms->last_status);
	// }
	exec_child(ms, cmd);
}

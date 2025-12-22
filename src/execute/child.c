/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:53:53 by klima-do          #+#    #+#             */
/*   Updated: 2025/12/22 19:33:22 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_child(t_shell *ms, t_command *cmd, int fd_in, int fd[2])
{
	char	*path;

	if (cmd->heredoc == 1)
		handle_heredoc(cmd);
	else if (fd_in != 0)
		handle_pipe_input(fd_in);
	if (cmd->infile)
		handle_infile(cmd);
	if (cmd->next)
		handle_pipe_output(fd);
	if (cmd->outfile)
		handle_outfile(cmd);
	path = get_path(ms->envp, cmd->argv[0]);
	if (!path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(cmd->argv[0], 2);
		_exit(127);
	}
	execve(path, cmd->argv, ms->envp);
	perror("execve");
	_exit(1);
}

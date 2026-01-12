/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:53:53 by klima-do          #+#    #+#             */
/*   Updated: 2026/01/11 22:20:26 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_child(t_shell *ms, t_command *cmd, int fd_in, int fd[2])
{
	char	*path;
	char	**envp;
	
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
	path = get_path(ms->env, cmd->argv[0]);
	if (!path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(cmd->argv[0], 2);
		_exit(127);
	}
	envp = hash_to_envp(ms->env);
	if (!envp)
	{
		free(path);
		_exit(1);
	}
	execve(path, cmd->argv, envp);
	perror("execve");
	free_envp(envp);
	free(path);
	_exit(1);
}

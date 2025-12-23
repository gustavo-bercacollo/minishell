/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 19:43:08 by klima-do          #+#    #+#             */
/*   Updated: 2025/12/22 21:05:50 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_cmd(t_shell *ms, t_ast *node)
{
	pid_t	pid;
	int		status;
	char	*path;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		set_default_signals_for_child();
		if (apply_redirections(node->cmd) <0)
			_exit (1);
		path = get_path(ms->envp, node->cmd->argv[0]);
		if (!path)
		{
			ft_putstr_fd(node->cmd->argv[0], 2);
			ft_putendl_fd(": command not found", 2);
			_exit(127);
		}
		execve(path, node->cmd->argv, ms->envp);
		perror("execve");
		_exit(126);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 19:43:08 by klima-do          #+#    #+#             */
/*   Updated: 2026/01/11 21:34:44 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_in_child(t_shell *ms, t_ast *node)
{
	char	**envp;
	char	*path;

	set_signals_child();
	if (apply_redirections(node->cmd) < 0)
		_exit(1);
	path = get_path(ms->env, node->cmd->argv[0]);
	if (!path)
	{
		ft_putstr_fd(node->cmd->argv[0], 2);
		ft_putendl_fd(": command not found", 2);
		_exit(127);
	}
	envp = hash_to_envp(ms->env);
	if (!envp)
	{
		free(path);
		perror("env");
		_exit(1);
	}
	execve(path, node->cmd->argv, envp);
	free_envp(envp);
	free(path);
	perror("execve");
	_exit(126);
}

int	execute_cmd(t_shell *ms, t_ast *node)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	set_signals_noninteractive();
	if (pid == 0)
		execute_in_child(ms, node);
	waitpid(pid, &status, 0);
	set_signals_interactive();
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

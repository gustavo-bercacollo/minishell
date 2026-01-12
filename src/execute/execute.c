/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:53:53 by klima-do          #+#    #+#             */
/*   Updated: 2026/01/11 21:34:39 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_builtin(const char *cmd, const char *name)
{
	return (!ft_strcmp(cmd, name));
}

int	is_builtin(const char *cmd)
{
	if (!cmd)
		return (0);
	if (check_builtin(cmd, "echo"))
		return (1);
	if (check_builtin(cmd, "cd"))
		return (1);
	if (check_builtin(cmd, "pwd"))
		return (1);
	if (check_builtin(cmd, "export"))
		return (1);
	if (check_builtin(cmd, "unset"))
		return (1);
	if (check_builtin(cmd, "env"))
		return (1);
	if (check_builtin(cmd, "exit"))
		return (1);
	return (0);
}

static int	restore_fds(int stdin_backup, int stdout_backup)
{
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
	return (0);
}

int	execute_builtin_with_redir(t_shell *ms, t_command *cmd)
{
	int	stdin_backup;
	int	stdout_backup;
	int	status;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	if (stdin_backup < 0 || stdout_backup < 0)
		return (perror("dup"), 1);
	apply_redirections(cmd);
	status = execute_builtin(ms, cmd);
	restore_fds(stdin_backup, stdout_backup);
	return (status);
}

int	execute_node(t_shell *ms, t_ast *node)
{
	if (!node)
		return (0);
	if (node->type == NODE_CMD)
	{
		if (node->cmd && node->cmd->argv
			&& is_builtin(node->cmd->argv[0]))
			return (execute_builtin_with_redir(ms, node->cmd));
		return (execute_cmd(ms, node));
	}
	if (node->type == NODE_PIPE)
		return (execute_pipe(ms, node));
	if (node->type == NODE_AND)
		return (execute_and(ms, node));
	if (node->type == NODE_OR)
		return (execute_or(ms, node));
	return (0);
}

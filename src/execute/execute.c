/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:53:53 by klima-do          #+#    #+#             */
/*   Updated: 2026/01/08 20:48:41 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(const char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
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
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
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

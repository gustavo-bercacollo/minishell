/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 14:24:27 by gbercaco          #+#    #+#             */
/*   Updated: 2025/12/10 17:26:27 by gbercaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(const char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "unset") == 0)
		return (1);
	return (0);
}
/*
int	execute_builtin(t_shell *ms, t_command *cmd)
{
	(void)ms;
	(void)cmd;
	if (!ft_strcmp(cmd->argv[0], "echo"))
		return (builtin_echo(cmd));
	else if (!ft_strcmp(cmd->argv[0], "cd"))
		return (builtin_cd(ms, cmd));
	else if (!ft_strcmp(cmd->argv[0], "pwd"))
		return (builtin_pwd());
	else if (!ft_strcmp(cmd->argv[0], "export"))
		return (builtin_export(ms, cmd));
	else if (!ft_strcmp(cmd->argv[0], "unset"))
		return (builtin_unset(ms, cmd));
	else if (!ft_strcmp(cmd->argv[0], "env"))
		return (builtin_env(ms));
	else if (!ft_strcmp(cmd->argv[0], "exit"))
		return (builtin_exit(ms, cmd));
	return (1);
}
*/
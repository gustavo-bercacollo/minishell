/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 14:24:27 by gbercaco          #+#    #+#             */
/*   Updated: 2026/01/11 21:31:29 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	is_builtin(const char *cmd)
// {
// 	if (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0
// 		|| ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "exit") == 0
// 		|| ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "pwd") == 0
// 		|| ft_strcmp(cmd, "unset") == 0)
// 		return (1);
// 	return (0);
// }

void	free_dictionary(char *key, char *value)
{
	free(key);
	free(value);
}

int	execute_builtin(t_shell *ms, t_command *cmd)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (1);
	if (!ft_strcmp(cmd->argv[0], "echo"))
		return (builtin_echo(cmd->argv));
	else if (!ft_strcmp(cmd->argv[0], "cd"))
		return (builtin_cd(ms, cmd->argv));
	else if (!ft_strcmp(cmd->argv[0], "pwd"))
		return (builtin_pwd());
	else if (!ft_strcmp(cmd->argv[0], "export"))
	{
		builtin_export(ms, cmd->argv);
		return (0);
	}
	else if (!ft_strcmp(cmd->argv[0], "unset"))
	{
		biutin_unset(ms, cmd->argv);
		return (0);
	}
	else if (!ft_strcmp(cmd->argv[0], "env"))
		return (biultin_env(ms->env));
	else if (!ft_strcmp(cmd->argv[0], "exit"))
		return (builtin_exit(ms, cmd->argv));
	return (1);
}

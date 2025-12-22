/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:46:12 by gbercaco          #+#    #+#             */
/*   Updated: 2025/12/22 20:48:37 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Expande um ÚNICO comando.
** Regra: se substituir argv[i], libera o antigo antes.
*/
void	expand_cmd(t_shell *ms, t_command *cmd)
{
	int		i;
	char	*var_name;
	char	*new_arg;

	if (!cmd || !cmd->argv)
		return ;
	i = 0;
	while (cmd->argv[i])
	{
		if (cmd->quoted && cmd->quoted[i] != 1)
		{
			var_name = process_arg(cmd->argv[i]);
			if (var_name)
			{
				new_arg = expand_variable_in_arg(
						ms, cmd->argv[i], var_name);
				if (new_arg)
				{
					free(cmd->argv[i]);
					cmd->argv[i] = new_arg;
				}
			}
		}
		i++;
	}
}

void	expand_ast(t_shell *ms, t_ast *node)
{
	if (!node)
		return ;
	if (node->type == NODE_CMD)
		expand_cmd(ms, node->cmd);
	else
	{
		expand_ast(ms, node->left);
		expand_ast(ms, node->right);
	}
}

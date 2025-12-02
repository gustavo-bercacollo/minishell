/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:46:12 by gbercaco          #+#    #+#             */
/*   Updated: 2025/12/02 16:05:57 by gbercaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand(t_shell *ms, t_command *cmd_list)
{
	t_command	*cmd;
	char		*var_name;
	int			i;

	cmd = cmd_list;
	while (cmd)
	{
		i = 0;
		while (cmd->argv && cmd->argv[i])
		{
			if (cmd->quoted[i] != 1)
			{
				var_name = process_arg(cmd->argv[i]);
				if (var_name)
					cmd->argv[i] = expand_variable_in_arg(ms, cmd->argv[i],
							var_name);
			}
			i++;
		}
		cmd = cmd->next;
	}
}

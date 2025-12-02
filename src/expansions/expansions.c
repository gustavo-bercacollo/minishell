/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:46:12 by gbercaco          #+#    #+#             */
/*   Updated: 2025/12/02 15:44:41 by gbercaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand(t_shell *ms, t_command *cmd_list)
{
	t_command	*cmd;
	char		*var_name;
	char		*value;
	char		*new_arg;
	int			i;

	cmd = cmd_list;
	while (cmd)
	{
		i = 0;
		while (cmd->argv && cmd->argv[i])
		{
			if (cmd->quoted[i] == 1)
			{
				i++;
				continue ;
			}
			var_name = process_arg(cmd->argv[i]);
			if (var_name)
			{
				value = get_variable_value(ms, var_name);
				new_arg = replace_var_in_arg(cmd->argv[i], var_name, value);
				free(value);
				free(var_name);
				free(cmd->argv[i]);
				cmd->argv[i] = new_arg;
			}
			i++;
		}
		cmd = cmd->next;
	}
}

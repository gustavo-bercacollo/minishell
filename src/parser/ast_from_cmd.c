/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_from_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:51:39 by klima-do          #+#    #+#             */
/*   Updated: 2026/01/11 23:01:15 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast 	*ast_from_cmd(t_command *cmd)
{
	t_ast	*node_cmd;

	node_cmd = malloc(sizeof(t_ast));
	if (!node_cmd)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	node_cmd->type = NODE_CMD;
	node_cmd->left = NULL;
	node_cmd->right = NULL;
	node_cmd->cmd = cmd;
	return (node_cmd);
}

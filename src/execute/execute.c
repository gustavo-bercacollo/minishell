/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:53:53 by klima-do          #+#    #+#             */
/*   Updated: 2025/12/22 20:39:58 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_node(t_shell *ms, t_ast *node)
{
	if (!node)
		return (0);
	if (node->type == NODE_CMD)
		return (execute_cmd(ms, node));
	if (node->type == NODE_PIPE)
		return (execute_pipe(ms, node));
	if (node->type == NODE_AND)
		return (execute_and(ms, node));
	if (node->type == NODE_OR)
		return (execute_or(ms,node));
	return (0);
}

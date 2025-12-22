/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_and.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 16:31:17 by klima-do          #+#    #+#             */
/*   Updated: 2025/12/22 16:34:08 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_and(t_shell *ms, t_ast *node)
{
	int	status;

	status = execute_node(ms, node->left);
	if (status == 0)
		return (execute_node(ms, node->right));
	return (status);
}
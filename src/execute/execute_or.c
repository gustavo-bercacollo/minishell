/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_or.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 16:34:30 by klima-do          #+#    #+#             */
/*   Updated: 2025/12/22 16:58:31 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_or(t_shell *ms, t_ast *node)
{
	int	status;

	status = execute_node(ms, node->left);
	if (status != 0)
		execute_node(ms, node->right);
	return (status);
}

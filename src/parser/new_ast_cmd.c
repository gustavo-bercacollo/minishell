/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_ast_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 16:01:33 by klima-do          #+#    #+#             */
/*   Updated: 2026/01/11 23:01:26 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*new_ast_node(t_node_type type, t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	node->type = type;
	node->left = left;
	node->right = right;
	node->cmd = NULL;
	node->token = NULL;
	return (node);
}

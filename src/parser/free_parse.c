/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 19:47:41 by gbercaco          #+#    #+#             */
/*   Updated: 2025/12/22 20:40:53 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_command(t_command *cmd)
{
	int	i;

	if (!cmd)
		return ;
	i = 0;
	while (cmd->argv && cmd->argv[i])
	{
		free(cmd->argv[i]);
		i++;
	}
	free(cmd->argv);
	if (cmd->infile)
		free(cmd->infile);
	if (cmd->outfile)
		free(cmd->outfile);
	if (cmd->quoted)
		free(cmd->quoted);
	free(cmd);
}

void	free_ast(t_ast *node)
{
	if (!node)
		return;
	free_ast(node->left);
	free_ast(node->right);
	if (node->token)
		free_token(node->token);
	if (node->type == NODE_CMD)
		free_command(node->cmd);
	free(node);
}


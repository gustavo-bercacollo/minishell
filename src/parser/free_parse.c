/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 19:47:41 by gbercaco          #+#    #+#             */
/*   Updated: 2025/12/08 21:10:16 by gbercaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_parse(t_command **cmd)
{
	t_command	*temp;
	int			i;

	if (!cmd || !*cmd)
		return ;
	while (*cmd)
	{
		temp = *cmd;
		*cmd = (*cmd)->next;
		i = -1;
		while (temp->argv && temp->argv[++i])
			free(temp->argv[i]);
		free(temp->argv);
		if (temp->infile)
			free(temp->infile);
		if (temp->outfile)
			free(temp->outfile);
		if (temp->quoted)
			free(temp->quoted);
		free(temp);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ultils_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:38:23 by gbercaco          #+#    #+#             */
/*   Updated: 2025/11/19 17:38:42 by gbercaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*new_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = 0;
	cmd->heredoc = 0;
	cmd->next = NULL;
	return (cmd);
}

void	add_arg(t_command *cmd, char *word)
{
	int		count;
	int		i;
	char	**new_argv;

	count = 0;
	if (cmd->argv)
		while (cmd->argv[count])
			count++;
	new_argv = malloc(sizeof(char *) * (count + 2));
	if (!new_argv)
		return ;
	i = -1;
	while (++i < count)
		new_argv[i] = cmd->argv[i];
	new_argv[count] = ft_strdup(word);
	new_argv[count + 1] = NULL;
	free(cmd->argv);
	cmd->argv = new_argv;
}

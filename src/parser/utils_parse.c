/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:38:23 by gbercaco          #+#    #+#             */
/*   Updated: 2025/12/02 15:06:54 by gbercaco         ###   ########.fr       */
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
	cmd->quoted = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = 0;
	cmd->heredoc = 0;
	cmd->heredoc_fd = -1;
	cmd->next = NULL;
	return (cmd);
}

void	add_arg(t_command *cmd, t_token *tok)
{
	int		count;
	int		i;
	char	**new_argv;
	int		*new_quoted;

	count = 0;
	if (cmd->argv)
		while (cmd->argv[count])
			count++;
	new_argv = malloc(sizeof(char *) * (count + 2));
	if (!new_argv)
		return ;
	new_quoted = malloc(sizeof(int) * (count + 2));
	if (!new_quoted)
	{
		free(new_argv);
		return ;
	}
	i = -1;
	while (++i < count)
	{
		new_argv[i] = cmd->argv[i];
		new_quoted[i] = cmd->quoted[i];
	}
	new_argv[count] = ft_strdup(tok->value);
	new_quoted[count] = tok->single_quoted;
	new_argv[count + 1] = NULL;
	new_quoted[count + 1] = 0;
	free(cmd->argv);
	free(cmd->quoted);
	cmd->argv = new_argv;
	cmd->quoted = new_quoted;
}

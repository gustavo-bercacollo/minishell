/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:38:23 by gbercaco          #+#    #+#             */
/*   Updated: 2025/12/02 17:38:35 by gbercaco         ###   ########.fr       */
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
	cmd->argc = 0;
	cmd->heredoc_fd = -1;
	cmd->next = NULL;
	return (cmd);
}

static void	replace_old_arrays(t_command *cmd, char **new_argv, int *new_quoted)
{
	free(cmd->argv);
	free(cmd->quoted);
	cmd->argv = new_argv;
	cmd->quoted = new_quoted;
}

static void	copy_old_args(t_command *cmd, char **new_argv, int *new_quoted)
{
	int	i;

	i = 0;
	while (i < cmd->argc)
	{
		new_argv[i] = cmd->argv[i];
		new_quoted[i] = cmd->quoted[i];
		i++;
	}
}

static void	add_new_arg_and_set_null(t_command *cmd, t_token *tok, char **new_argv,
		int *new_quoted)
{
	new_argv[cmd->argc] = ft_strdup(tok->value);
	new_quoted[cmd->argc] = tok->single_quoted;
	new_argv[cmd->argc + 1] = NULL;
	new_quoted[cmd->argc + 1] = 0;
}

void	add_arg(t_command *cmd, t_token *tok)
{
	char	**new_argv;
	int		*new_quoted;

	new_argv = malloc(sizeof(char *) * (cmd->argc + 2));
	if (!new_argv)
		return ;
	new_quoted = malloc(sizeof(int) * (cmd->argc + 2));
	if (!new_quoted)
	{
		free(new_argv);
		return ;
	}
	copy_old_args(cmd, new_argv, new_quoted);
	add_new_arg_and_set_null(cmd, tok, new_argv, new_quoted);
	replace_old_arrays(cmd, new_argv, new_quoted);
	cmd->argc++;
}

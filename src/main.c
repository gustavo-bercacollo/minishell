/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 14:17:43 by gbercaco          #+#    #+#             */
/*   Updated: 2025/11/19 19:23:17 by gbercaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_commands(t_command *cmd)
{
	int	i;

	while (cmd)
	{
		printf("\n");
		i = 0;
		if (cmd->argv)
		{
			while (cmd->argv[i])
			{
				printf("ARG[%d]: %s\n", i, cmd->argv[i]);
				i++;
			}
		}
		else
			printf("(no argv)\n");
		if (cmd->infile)
			printf("INFILE   : %s\n", cmd->infile);
		if (cmd->outfile)
			printf("OUTFILE  : %s\n", cmd->outfile);
		printf("APPEND   : %d\n", cmd->append);
		printf("HEREDOC  : %d\n", cmd->heredoc);
		cmd = cmd->next;
	}
}

int	main(void)
{
	char		*line;
	t_token		*tokens;
	t_command	*cmds;

	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		tokens = tokenize(line);
		cmds = parse(tokens);
		print_commands(cmds);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 16:47:34 by gbercaco          #+#    #+#             */
/*   Updated: 2025/11/23 16:49:44 by gbercaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell		ms;
	char		*line;
	t_token		*tokens;
	t_command	*cmds;

	(void)argc;
	(void)argv;
	ms.envp = envp;
	ms.last_status = 0;
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		tokens = tokenize(line);
		cmds = parse(tokens);
		if (cmds)
		{
			ms.last_status = execute_single(&ms, cmds);
			printf("Status do comando: %d\n", ms.last_status);
		}
	}
	return (0);
}

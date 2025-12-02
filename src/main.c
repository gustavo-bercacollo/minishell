/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:45:06 by gbercaco          #+#    #+#             */
/*   Updated: 2025/12/02 18:07:07 by gbercaco         ###   ########.fr       */
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
		expand(&ms, cmds);
		if (cmds)
			ms.last_status = execute(&ms, cmds);
	}
	return (0);
}

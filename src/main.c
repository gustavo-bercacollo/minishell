/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:45:06 by gbercaco          #+#    #+#             */
/*   Updated: 2025/12/10 16:21:05 by gbercaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(char **line, t_token **tokens, t_command **cmds, t_shell *ms)
{
	while (1)
	{
		*line = readline("minishell> ");
		if (!*line)
			break ;
		if (**line)
			add_history(*line);
		*tokens = tokenize(*line);
		*cmds = parse(*tokens);
		expand(ms, *cmds);
		if (*cmds)
			ms->last_status = execute(ms, *cmds);
		free_tokens(tokens);
		free_parse(cmds);
		free(*line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		ms;
	char		*line;
	t_token		*tokens;
	t_command	*cmds;

	line = NULL;
	tokens = NULL;
	cmds = NULL;
	(void)argc;
	(void)argv;
	ms.envp = envp;
	ms.last_status = 0;
	init_signals();
	init_shell(&line, &tokens, &cmds, &ms);
	clear_history();
	return (0);
}

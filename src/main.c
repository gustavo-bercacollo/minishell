/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:45:06 by gbercaco          #+#    #+#             */
/*   Updated: 2026/01/08 20:24:54 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(char **line, t_token **tokens, t_ast **ast, t_shell *ms)
{
	while (1)
	{
		g_interrupted = 1;
		*line = readline("minishell> ");
		g_interrupted = 0;
		if (!*line)
			break ;
		if (**line)
			add_history(*line);
		*tokens = tokenize(*line);
		*ast = parse_ast(tokens);
		expand_ast(ms, *ast);
		if (*ast)
    	ms->last_status = execute_node(ms, *ast);
		if (ms->should_exit)
		{
		    free_tokens(tokens);
		    free_ast(*ast);
		    break;
		}
		free_tokens(tokens);
		free_ast(*ast);
		*tokens = NULL;
		*ast = NULL;
		free(*line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		ms;
	char		*line;
	t_token		*tokens;
	t_ast		*ast;

	line = NULL;
	tokens = NULL;
	ast = NULL;
	(void)argc;
	(void)argv;
	ms.env = env_hash_init(envp);
	ms.last_status = 0;
	init_signals();
	init_shell(&line, &tokens, &ast, &ms);
	clear_history();
	free_hash(ms.env);
	return (0);
}

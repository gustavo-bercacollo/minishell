/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:45:06 by gbercaco          #+#    #+#             */
/*   Updated: 2026/01/14 18:11:41 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cleanup_loop(char **line, t_token **tokens, t_ast **ast)
{
	free_tokens(tokens);
	free_ast(*ast);
	free(*line);
	*tokens = NULL;
	*ast = NULL;
}

static int	process_line(char **line, t_token **tokens,
		t_ast **ast, t_shell *ms)
{
	*tokens = tokenize(*line);
	*ast = parse_ast(tokens);
	expand_ast(ms, *ast);
	if (*ast)
		ms->last_status = execute_node(ms, *ast);
	if (ms->should_exit)
	{
		cleanup_loop(line, tokens, ast);
		return (1);
	}
	return (0);
}

void	init_shell(char **line, t_token **tokens, t_ast **ast, t_shell *ms)
{
	while (1)
	{
		set_signals_interactive();
		*line = readline("minishell> ");
		if (!*line)
			break ;
		if (**line)
			add_history(*line);
		if (process_line(line, tokens, ast, ms))
			break ;
		cleanup_loop(line, tokens, ast);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		ms;
	char		*line;
	t_token		*tokens;
	t_ast		*ast;

	(void)argc;
	(void)argv;
	line = NULL;
	tokens = NULL;
	ast = NULL;
	ms.env = env_hash_init(envp);
	ms.last_status = 0;
	ms.should_exit = 0;
	set_signals_interactive();
	init_shell(&line, &tokens, &ast, &ms);
	clear_history();
	free_hash(ms.env);
	return (ms.exit_status);
}

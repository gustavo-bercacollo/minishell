/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 14:17:43 by gbercaco          #+#    #+#             */
/*   Updated: 2025/11/18 17:53:33 by gbercaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *tok)
{
	while (tok)
	{
		if (tok->type == TOK_WORD)
			printf("WORD      : %s\n", tok->value);
		else if (tok->type == TOK_PIPE)
			printf("PIPE      : %s\n", tok->value);
		else if (tok->type == TOK_REDIR_IN)
			printf("REDIR_IN  : %s\n", tok->value);
		else if (tok->type == TOK_REDIR_OUT)
			printf("REDIR_OUT : %s\n", tok->value);
		else if (tok->type == TOK_REDIR_APPEND)
			printf("APPEND    : %s\n", tok->value);
		else if (tok->type == TOK_HEREDOC)
			printf("HEREDOC   : %s\n", tok->value);
		tok = tok->next;
	}
}

int	main(void)
{
	char		*line;
	t_token		*tokens;

	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		tokens = tokenize(line);
		print_tokens(tokens);
	}
	return (0);
}

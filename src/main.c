/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 14:17:43 by gbercaco          #+#    #+#             */
/*   Updated: 2025/11/17 18:20:37 by gbercaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	// char	*line;

	// while (1)
	// {
	// 	line = readline("minishell> ");
	// 	if (!line)
	// 		break ;
	// 	if (*line)
	// 		add_history(line);
	// 	free(line);
	// }
	// return (0);

	t_token *t;

	t = new_token(ft_strdup("ls"), TOK_PIPE);

	printf("value = %s\n", t->value);
	printf("type  = %d\n", t->type);

	free(t->value);
	free(t);
}

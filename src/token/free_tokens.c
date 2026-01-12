/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:02:03 by gbercaco          #+#    #+#             */
/*   Updated: 2026/01/11 21:35:35 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(t_token *token)
{
	if (!token)
		return ;
	if (token->value)
		free(token->value);
	free(token);
}

void	free_tokens(t_token **tokens)
{
	t_token	*temp;

	if (!tokens || !*tokens)
		return ;
	while (*tokens)
	{
		temp = *tokens;
		*tokens = (*tokens)->next;
		if (temp->value)
			free(temp->value);
		free(temp);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:17:54 by klima-do          #+#    #+#             */
/*   Updated: 2025/10/02 17:35:39 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*pop(t_stack *stack)
{
	t_list	*node;
	void	*content ;

	node = stack->top;
	if (!stack || !stack->top)
		return (NULL);
	content = node->content;
	stack->top = node->next;
	free(node);
	stack->size--;
	return (content);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 19:46:45 by klima-do          #+#    #+#             */
/*   Updated: 2025/10/01 19:03:47 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	stack_clear(t_stack *stack, void (*del)(void *))
{
	t_list	*node;
	t_list	*next;

	if (!stack)
		return ;
	node = stack->top;
	while (node)
	{
		next = node->next;
		if (del)
			del(node->content);
		free(node);
		node = next;
	}
	stack->top = NULL;
}

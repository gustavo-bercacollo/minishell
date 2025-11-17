/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:16:40 by klima-do          #+#    #+#             */
/*   Updated: 2025/10/02 17:36:21 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	select_sort(t_stack	*stack)
{
	t_list	*node_to_comp;
	t_list	*node_target;
	t_list	*min_node;
	int		temp;

	node_to_comp = stack->top;
	while (node_to_comp)
	{
		min_node = node_to_comp;
		node_target = node_to_comp->next;
		while (node_target)
		{
			if (*(int *)node_target->content < *(int *)min_node->content)
				min_node = node_target;
			node_target = node_target->next;
		}
		if (min_node != node_to_comp)
		{
			temp = *(int *)node_to_comp->content;
			*(int *)node_to_comp->content = *(int *)min_node->content;
			*(int *)min_node->content = temp;
		}
		node_to_comp = node_to_comp->next;
	}
}

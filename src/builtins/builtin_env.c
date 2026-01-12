/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:06:35 by klima-do          #+#    #+#             */
/*   Updated: 2026/01/11 21:31:22 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	biultin_env(t_hash *env)
{
	size_t			i;
	t_hash_node		*node;

	i = 0;
	while (i < env->size)
	{
		node = env->buckets[i];
		while (node)
		{
			if (node->value)
				printf("%s=%s\n", node->key, node->value);
			node = node->next;
		}
		i++;
	}
	return (0);
}

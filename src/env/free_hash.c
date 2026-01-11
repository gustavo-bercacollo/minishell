/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_hash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 17:27:45 by klima-do          #+#    #+#             */
/*   Updated: 2026/01/08 17:31:08 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_hash(t_hash *hash)
{
	size_t		i;
	t_hash_node	*node;
	t_hash_node	*next;

	if (!hash)
		return ;
	i = 0;
	while (i < hash->size)
	{
		node = hash->buckets[i];
		while (node)
		{
			next = node->next;
			free(node->key);
			free(node->value);
			free(node);
			node = next;
		}
		i++;
	}
	free(hash->buckets);
	free(hash);
}
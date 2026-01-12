/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 20:28:01 by klima-do          #+#    #+#             */
/*   Updated: 2026/01/11 21:30:47 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

void	free_node(t_hash_node *node)
{
	free(node->key);
	free(node->value);
}

void	hash_unset(t_hash *hash, char *key)
{
	unsigned int	index;
	t_hash_node		*current;
	t_hash_node		*prev;

	index = hash_func(key, hash->size);
	current = hash->buckets[index];
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			break ;
		prev = current;
		current = current->next;
	}
	if (!current)
		return ;
	if (prev == NULL)
		hash->buckets[index] = current->next;
	else
		prev->next = current->next;
	free_node(current);
	free(current);
}

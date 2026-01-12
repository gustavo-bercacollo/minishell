/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 19:14:28 by klima-do          #+#    #+#             */
/*   Updated: 2026/01/11 22:32:37 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

void	hash_set(t_hash *hash, char *key, char *value)
{
	unsigned int	index;
	t_hash_node		*current;
	t_hash_node		*new;

	index = hash_func(key, hash->size);
	current = hash->buckets[index];
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
	new = malloc(sizeof(t_hash_node));
	if (!new)
		return ;
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = hash->buckets[index];
	hash->buckets[index] = new;
	hash->count++;
}

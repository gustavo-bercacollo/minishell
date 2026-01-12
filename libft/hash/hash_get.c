/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 20:21:19 by klima-do          #+#    #+#             */
/*   Updated: 2026/01/11 21:30:24 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

t_hash_node	*hash_get(t_hash *hash, char *key)
{
	unsigned int	index;
	t_hash_node		*current;

	if (!hash || !key)
		return (NULL);
	index = hash_func(key, hash->size);
	current = hash->buckets[index];
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 18:44:53 by klima-do          #+#    #+#             */
/*   Updated: 2026/01/11 21:29:50 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

t_hash	*hash_create(size_t	initial_size)
{
	t_hash	*hash;

	hash = malloc(sizeof(*hash));
	if (!hash)
		return (NULL);
	hash->size = initial_size;
	hash->count = 0;
	hash->buckets = ft_calloc(hash->size, sizeof(t_hash_node *));
	if (!hash->buckets)
	{
		free(hash);
		return (NULL);
	}
	return (hash);
}

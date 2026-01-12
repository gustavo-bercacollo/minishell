/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_node_create.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 19:10:57 by klima-do          #+#    #+#             */
/*   Updated: 2026/01/11 21:30:34 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

t_hash_node	*create_hash_node(char *key, char *value)
{
	t_hash_node	*node;

	node = malloc(sizeof(t_hash_node));
	if (!node)
	{
		return (NULL);
	}
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}

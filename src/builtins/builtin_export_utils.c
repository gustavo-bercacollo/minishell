/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:30:27 by gbercaco          #+#    #+#             */
/*   Updated: 2026/01/14 16:40:35 by gbercaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	compare_nodes(const void *a, const void *b)
{
	t_hash_node	*node_a;
	t_hash_node	*node_b;

	node_b = *(t_hash_node **)b;
	node_a = *(t_hash_node **)a;
	return (ft_strcmp(node_a->key, node_b->key));
}

void	collect_nodes(t_hash *hash, t_hash_node **nodes)
{
	size_t		count;
	size_t		b;
	t_hash_node	*node;

	count = 0;
	b = 0;
	while (b < hash->size)
	{
		node = hash->buckets[b];
		while (node)
		{
			nodes[count++] = node;
			node = node->next;
		}
		b++;
	}
	nodes[count] = NULL;
}

void	print_export_sorted(t_hash *hash)
{
	t_hash_node	**nodes;
	size_t		i;

	nodes = malloc(sizeof(t_hash_node *) * (hash->count + 1));
	if (!nodes)
		return ;
	collect_nodes(hash, nodes);
	qsort(nodes, hash->count, sizeof(t_hash_node *), compare_nodes);
	i = 0;
	while (i < hash->count)
	{
		printf("declare -x %s=\"%s\"\n", nodes[i]->key, nodes[i]->value);
		i++;
	}
	free(nodes);
}

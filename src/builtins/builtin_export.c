/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 20:16:43 by klima-do          #+#    #+#             */
/*   Updated: 2026/01/11 22:22:09 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_valid_identifier(char *str)
{
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	str++;
	while (*str && *str != '=')
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

void	export_single(t_hash *hash, char *str)
{
	char	*key;
	char	*value;
	char	*position;

	if (!is_valid_identifier(str))
	{
		ft_putendl_fd("export: not a valid identifier", 2);
		return ;
	}
	position = ft_strchr(str, '=');
	if (!position)
	{
		key = ft_strdup(str);
		if (!hash_get(hash, key))
			hash_set(hash, key, "");
		free(key);
		return ;
	}
	key = ft_substr(str, 0, position - str);
	value = ft_strdup(position + 1);
	hash_set(hash, key, value);
	free(key);
	free(value);
}

static int	compare_nodes(const void *a, const void *b)
{
	t_hash_node	*node_a;
	t_hash_node	*node_b;

	node_b = *(t_hash_node **)b;
	node_a = *(t_hash_node **)a;
	return (ft_strcmp(node_a->key, node_b->key));
}

static void	print_export_sorted(t_hash *hash)
{
	t_hash_node	**nodes;
	size_t		count;
	size_t		i;
	size_t		b;
	t_hash_node	*node;

	nodes = malloc(sizeof(t_hash_node *) * (hash->count + 1));
	if (!nodes)
		return ;
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
	qsort(nodes, count, sizeof(t_hash_node *), compare_nodes);
	i = 0;
	while (i < count)
	{
		printf("declare -x %s=\"%s\"\n", nodes[i]->key, nodes[i]->value);
		i++;
	}
	free(nodes);
}

int	builtin_export(t_shell *sh, char **argv)
{
	size_t	b;

	if (!argv[1])
	{
		print_export_sorted(sh->env);
		return (0);
	}
	b = 1;
	while (argv[b])
	{
		export_single(sh->env, argv[b]);
		b++;
	}
	return (0);
}

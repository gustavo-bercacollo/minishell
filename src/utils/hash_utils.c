/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 18:07:04 by gbercaco          #+#    #+#             */
/*   Updated: 2026/01/14 18:07:22 by gbercaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*hash_get_value(t_hash *hash, char *key)
{
	t_hash_node	*node;

	node = hash_get(hash, key);
	if (!node)
		return (NULL);
	return (node->value);
}

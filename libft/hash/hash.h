/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 17:59:37 by klima-do          #+#    #+#             */
/*   Updated: 2026/01/11 22:27:11 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H

# include "../libft.h"

typedef struct s_hash_node
{
	char				*key;
	char				*value;
	struct s_hash_node	*next;
}	t_hash_node;

typedef struct s_hash
{
	t_hash_node	**buckets;
	size_t		size;
	size_t		count;
}	t_hash;

t_hash			*hash_create(size_t initial_size);
t_hash_node		*create_hash_node(char *key, char *value);
unsigned int	hash_func(const char *key, size_t size);
void			hash_set(t_hash *hash, char *key, char *value);
t_hash_node		*hash_get(t_hash *hash, char *key);
void			hash_unset(t_hash *hash, char *key);

#endif
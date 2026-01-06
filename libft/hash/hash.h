/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 17:59:37 by klima-do          #+#    #+#             */
/*   Updated: 2025/12/27 19:39:49 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_SIZE
#define HASH_SIZE
#define HASH_SIZE

#include "../libft.h"

typedef struct s_hash_node
{
	char 				*key;
	char				*value;
	struct s_hash_node 	*next;
}	t_hash_node;

typedef struct s_hash
{
	t_hash_node		**buckets;
	size_t			size;
	size_t			count;
}	t_hash;

t_hash	*hash_create(size_t	initial_size);
void		hash_set(t_hash *hash, char *key, char *value);
char		*hash_get(t_hash *hash, char *key);
void		hash_unset(t_hash *hash, char *key);
void		hash_clear(t_hash *hash);
unsigned int	hash_func(const char *key, size_t	size);

t_hash_node	*create_hash_node(char *key, char *value);

#endif
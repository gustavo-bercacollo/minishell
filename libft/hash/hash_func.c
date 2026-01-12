/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 19:06:13 by klima-do          #+#    #+#             */
/*   Updated: 2026/01/11 21:29:55 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

unsigned int	hash_func(const char *key, size_t	size)
{
	unsigned int	hash;

	hash = 0;
	while (*key)
	{
		hash = hash * 31 + (unsigned char)(*key);
		key++;
	}
	return ((hash) % size);
}

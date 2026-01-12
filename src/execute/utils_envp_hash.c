/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_envp_hash.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 15:13:42 by klima-do          #+#    #+#             */
/*   Updated: 2026/01/11 21:39:19 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_split3(const char *s1, const char *s2, const char *s3)
{
	char	*res;
	size_t	i;
	size_t	j;

	if (!s1 || !s2 || !s3)
		return (NULL);
	res = malloc(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		res[i++] = s1[j++];
	j = 0;
	while (s2[j])
		res[i++] = s2[j++];
	j = 0;
	while (s3[j])
		res[i++] = s3[j++];
	res[i] = '\0';
	return (res);
}

void	free_envp(char **envp)
{
	size_t	i;
	 
	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}

char	**hash_to_envp(t_hash *hash)
{
	char		**envp;
	t_hash_node	*node;
	size_t		i;
	size_t		b;

	if (!hash)
		return (NULL);
	envp = malloc(sizeof(char *) * (hash->count + 1));
	if (!envp)
		return (NULL);
	i = 0;
	b = 0;
	while (b < hash->size)
	{
		node = hash->buckets[b];
		while (node)
		{
			if (node->value)
				envp[i++] = ft_split3(node->key, "=", node->value);
			node = node->next;
		}
		b++;
	}
	envp[i] = NULL;
	return (envp);
}

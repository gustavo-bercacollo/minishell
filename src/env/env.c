/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:53:53 by klima-do          #+#    #+#             */
/*   Updated: 2026/01/11 22:20:31 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_hash	*env_hash_init(char **env)
{
	t_hash	*hash;
	char	*key;
	char	*value;
	char	*position;
	int		i;

	hash = hash_create(128);
	if (!hash)
		return (NULL);
	i = 0;
	while (env[i])
	{
		position = ft_strchr(env[i], '=');
		if (position)
		{
			key = ft_substr(env[i], 0, position - env[i]);
			value = ft_strdup(position + 1);
			if (key && value)
			{
				hash_set(hash, key, value);
				free(key);
				free(value);
			}
			else
			{
				free(key);
				free(value);
			}
		}
		i++;
	}
	return (hash);
}

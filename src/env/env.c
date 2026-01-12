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

static void	add_env_variable(t_hash *hash, char *env_str)
{
	char	*key;
	char	*value;
	char	*position;

	position = ft_strchr(env_str, '=');
	if (!position)
		return ;
	key = ft_substr(env_str, 0, position - env_str);
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

t_hash	*env_hash_init(char **env)
{
	t_hash	*hash;
	int		i;

	hash = hash_create(128);
	if (!hash)
		return (NULL);
	i = 0;
	while (env[i])
	{
		add_env_variable(hash, env[i]);
		i++;
	}
	return (hash);
}

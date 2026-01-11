/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:18:06 by klima-do          #+#    #+#             */
/*   Updated: 2026/01/08 16:23:49 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_env_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	return (envp[i] + 5);
}

char	*hash_get_value(t_hash *hash, char *key)
{
	t_hash_node	*node;

	node = hash_get(hash, key);
	if (!node)
		return (NULL);
	return (node->value);
}

void debug_env(t_hash *env)
{
	size_t i;
	t_hash_node *n;

	i = 0;
	while (i < env->size)
	{
		n = env->buckets[i];
		while (n)
		{
			ft_putstr_fd("KEY=[", 2);
			ft_putstr_fd(n->key, 2);
			ft_putstr_fd("] VALUE=[", 2);
			ft_putstr_fd(n->value, 2);
			ft_putendl_fd("]", 2);
			n = n->next;
		}
		i++;
	}
}

char	*get_path(t_hash *env, char *cmd)
{
	char	*path_env;
	char	**dirs;
	char	*path;
	char	*tmp;
	int		i;

	if (!cmd || ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_env = hash_get_value(env, "PATH");
	if (!path_env)
		return (NULL);
	dirs = ft_split(path_env, ':');
	if (!dirs)
		return (NULL);
	i = 0;
	while (dirs[i])
	{
		tmp = ft_strjoin(dirs[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, X_OK) == 0)
		{
			ft_free_split(dirs);
			return (path);
		}
		free(path);
		i++;
	}
	ft_free_split(dirs);
	return (NULL);
}

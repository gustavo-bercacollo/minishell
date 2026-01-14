/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 18:04:24 by gbercaco          #+#    #+#             */
/*   Updated: 2026/01/14 18:05:16 by gbercaco         ###   ########.fr       */
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

void	debug_env(t_hash *env)
{
	size_t		i;
	t_hash_node	*n;

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

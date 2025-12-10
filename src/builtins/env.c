/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:53:53 by klima-do          #+#    #+#             */
/*   Updated: 2025/12/10 17:04:50 by gbercaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env_node(t_env **env_lst, char *env_line)
{
	char	*postion;
	t_env	*env_node;

	postion = ft_strchr(env_line, '=');
	if (!postion)
		return ;
	env_node = malloc(sizeof(t_env));
	if (!env_node)
		return ;
	env_node->key = ft_substr(env_line, 0, postion - env_line);
	env_node->value = ft_strdup(postion + 1);
	env_node->next = NULL;
	env_add_back(env_lst, env_node);
}

void	env_add_back(t_env **env_lst, t_env *new)
{
	t_env	*last;

	if (!env_lst || !new)
		return ;
	if (*env_lst == NULL)
	{
		*env_lst = new;
		return ;
	}
	last = *env_lst;
	while (last->next)
		last = last->next;
	last->next = new;
}

t_env	*get_env(char **env)
{
	int		i;
	t_env	*node;

	i = 0;
	node = NULL;
	while (env[i])
	{
		add_env_node(&node, env[i]);
		i++;
	}
	return (node);
}

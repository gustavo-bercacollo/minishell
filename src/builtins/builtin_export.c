/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 20:16:43 by klima-do          #+#    #+#             */
/*   Updated: 2025/11/20 20:33:10 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env_node(char **envp, char *env_line)
{
	char	*equal;
	t_env	*node;

	equal = ft_strchr(env_line, '=');
	if(!equal)
		return ;
	node = malloc(sizeof(t_env));
	node->key = ft_substr(env_line, 0, equal - env_line);
	node->value = ft_strdup(equal + 1);
	node->next = NULL;

	
}
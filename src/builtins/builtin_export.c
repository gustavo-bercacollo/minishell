/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 20:16:43 by klima-do          #+#    #+#             */
/*   Updated: 2026/01/08 18:14:40 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_valid_identifier(char *str)
{
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	str++;
	while (*str && *str != '=')
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

void	export_single(t_hash *hash, char *str)
{
	char	*key;
	char	*value;
	char	*position;

	if (!is_valid_identifier(str))
	{
		ft_putendl_fd("export: not a valid identifier", 2);
		return;
	}
	position = ft_strchr(str, '=');
	if (!position)
	{
		key = ft_strdup(str);
		if (!hash_get(hash, key))
			hash_set(hash, key, "");
		free(key);
		return;
	}
	key = ft_substr(str, 0, position - str);
	value = ft_strdup(position + 1);
	hash_set(hash, key, value);
	free(key);
	free(value);
}

int	builtin_export(t_shell *sh, char **argv)
{
	int	i;

	if (!argv[1])
	{
		// Criar função para imrprimir as variaveis formatadas
		return (1);
	}
	i = 1;
	while (argv[i])
	{
		export_single(sh->env, argv[i]);
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 20:16:43 by klima-do          #+#    #+#             */
/*   Updated: 2026/01/14 16:34:28 by gbercaco         ###   ########.fr       */
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
		return ;
	}
	position = ft_strchr(str, '=');
	if (!position)
	{
		key = ft_strdup(str);
		if (!hash_get(hash, key))
			hash_set(hash, key, "");
		free(key);
		return ;
	}
	key = ft_substr(str, 0, position - str);
	value = ft_strdup(position + 1);
	hash_set(hash, key, value);
	free(key);
	free(value);
}

int	builtin_export(t_shell *sh, char **argv)
{
	size_t	b;

	if (!argv[1])
	{
		print_export_sorted(sh->env);
		return (0);
	}
	b = 1;
	while (argv[b])
	{
		export_single(sh->env, argv[b]);
		b++;
	}
	return (0);
}

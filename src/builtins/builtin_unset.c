/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 19:39:42 by klima-do          #+#    #+#             */
/*   Updated: 2026/01/07 16:57:48 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_one(t_hash *hash, char *str)
{
	if (!str || !*str)
		return;
	hash_unset(hash, str);
}

void	biutin_unset(t_shell *sh, char **argv)
{
	int	index;

	index = 1;
	while(argv[index])
	{
		unset_one(sh->env, argv[index]);
		index++;
	}
}
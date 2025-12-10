/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:06:35 by klima-do          #+#    #+#             */
/*   Updated: 2025/12/10 17:04:12 by gbercaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	biultin_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\nexport", envp[i]);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	biultin_envp(envp);
}

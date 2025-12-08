/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:06:35 by klima-do          #+#    #+#             */
/*   Updated: 2025/11/20 20:02:23 by klima-do         ###   ########.fr       */
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

int main(int argc, char **argv, char **envp)
{
	biultin_envp(envp);
}
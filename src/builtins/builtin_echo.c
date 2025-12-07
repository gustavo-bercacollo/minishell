/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 14:57:49 by klima-do          #+#    #+#             */
/*   Updated: 2025/12/03 15:41:54 by gbercaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtin_echo(char **argv)
{
	int	i;
	int	new_l;

	i = 1;
	new_l = 1;
	if (argv[i] && !ft_strncmp(argv[i], "-n", 2))
	{
		new_l = 0;
		while (argv[i] && !ft_strncmp(argv[i], "-n", 2))
			i++;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (new_l)
		printf("\n");
	return (0);
}

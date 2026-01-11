/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 18:00:24 by klima-do          #+#    #+#             */
/*   Updated: 2026/01/08 18:25:25 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_numeric(const char *s)
{
	int	i;

	if (!s || !*s)
		return (0);
	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int builtin_exit(t_shell *ms, char **argv)
{
    long status;

    ft_putendl_fd("exit", STDERR_FILENO);
    if (argv[1] && argv[2])
    {
        ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
        return (1); // não sai
    }
    if (argv[1])
    {
        if (!is_numeric(argv[1]))
        {
            ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
            ft_putstr_fd(argv[1], STDERR_FILENO);
            ft_putendl_fd(": numeric argument required", STDERR_FILENO);
            status = 2;
        }
        else
            status = ft_atol(argv[1]);
    }
    else
        status = ms->last_status;
    ms->should_exit = 1;
    ms->exit_status = (unsigned char)status;
    return (0);
}

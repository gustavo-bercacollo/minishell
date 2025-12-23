/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 19:15:45 by gbercaco          #+#    #+#             */
/*   Updated: 2025/12/23 00:16:08 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_interrupted = 0;

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	if (g_interrupted)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}


void	init_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	set_default_signals_for_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

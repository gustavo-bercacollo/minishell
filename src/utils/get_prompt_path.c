/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:01:42 by klima-do          #+#    #+#             */
/*   Updated: 2025/12/03 15:42:40 by gbercaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path_prompt(void)
{
	char	*cwd;
	char	*start;

	cwd = getcwd(NULL, 0);
	start = ft_strnstr(cwd, "Minihell", ft_strlen(cwd));
	if (start)
		return (ft_strdup(start));
	start = ft_strrchr(cwd, '/');
	if (start)
		return (ft_strdup(start + 1));
	return (cwd);
}

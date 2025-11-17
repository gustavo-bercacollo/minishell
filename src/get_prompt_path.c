/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:01:42 by klima-do          #+#    #+#             */
/*   Updated: 2025/11/17 16:21:32 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path_prompt(void)
{
	char	*cwd;
	char	*start;

	cwd = getcwd(NULL, 0);
	start = ft_strnstr(cwd, "Minihell", ft_strlen(cwd));
	if(start)
		return(ft_strdup(start));
	start = ft_strrchr(cwd, '/');
	if(start)
		return(ft_strdup(start + 1));
	return (cwd);
}
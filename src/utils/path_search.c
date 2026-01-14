/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 18:02:32 by gbercaco          #+#    #+#             */
/*   Updated: 2026/01/14 18:04:07 by gbercaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_path_in_dir(char *dir, char *cmd)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(dir, "/");
	path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (access(path, X_OK) == 0)
		return (path);
	free(path);
	return (NULL);
}

char	*search_in_dirs(char **dirs, char *cmd)
{
	char	*path;
	int		i;

	i = 0;
	while (dirs[i])
	{
		path = check_path_in_dir(dirs[i], cmd);
		if (path)
		{
			ft_free_split(dirs);
			return (path);
		}
		i++;
	}
	ft_free_split(dirs);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:18:06 by klima-do          #+#    #+#             */
/*   Updated: 2025/11/17 18:00:39 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_env_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	return (envp[i] + 5);
}

char	*get_path(char **envp, char *cmd)
{
	char	*envp_path;
	int		j;
	char	**dirs;
	char	*path;
	char	*temp;

	envp_path = find_env_path(envp);
	dirs = ft_split(envp_path, ':');
	j = 0;
	while (dirs[j])
	{
		temp = ft_strjoin(dirs[j], "/");
		path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(path, X_OK) == 0)
		{
			ft_free_split(dirs);
			return (path);
		}
		free(path);
		j++;
	}
	ft_free_split(dirs);
	return (NULL);
}

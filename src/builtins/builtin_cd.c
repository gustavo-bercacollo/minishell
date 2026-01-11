/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 17:53:36 by klima-do          #+#    #+#             */
/*   Updated: 2026/01/08 18:23:23 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_error(const char *msg)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putendl_fd((char *)msg, STDERR_FILENO);
	return (1);
}


void	env_set(t_hash *env, const char *key, const char *value)
{
	char	*k;
	char	*v;

	if (!env || !key || !value)
		return;
	k = ft_strdup(key);
	v = ft_strdup(value);
	if (!k || !v)
	{
		free(k);
		free(v);
		return;
	}
	hash_set(env, k, v);
}


int	builtin_cd(t_shell *ms, char **argv)
{
	char	*path;
	char	cwd[128];

	if (argv[1] == NULL)
		path = hash_get_value(ms->env, "HOME");
	else if (ft_strcmp(argv[1], "-") == 0)
		path = hash_get_value(ms->env, "OLDPWD");
	else
		path = argv[1];
	if (!path)
		return (cd_error("HOME or OLDPWD not set"));
	if (getcwd(cwd, sizeof(cwd)))
		env_set(ms->env, "OLDPWD", cwd);
	if (chdir(path) != 0)
		return (perror("cd"), 1);
	if (getcwd(cwd, sizeof(cwd)))
		env_set(ms->env, "PWD", cwd);
	if (argv[1] && ft_strcmp(argv[1], "-") == 0)
		ft_putendl_fd(cwd, STDOUT_FILENO);
	return (0);
}

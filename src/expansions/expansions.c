/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:46:12 by gbercaco          #+#    #+#             */
/*   Updated: 2025/11/30 20:19:37 by gbercaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_var_name(char *arg, int j)
{
	int	start;
	int	k;

	start = j + 1;
	if (arg[start] == '?')
		return (ft_strdup("?"));
	if (!ft_isalpha(arg[start]) && arg[start] != '_')
		return (ft_strdup(""));
	k = start;
	while (ft_isalnum(arg[k]) || arg[k] == '_')
		k++;
	return (ft_substr(arg, start, k - start));
}

char	*process_arg(char *arg)
{
	int		single_quotation;
	int		double_quotation;
	int		i;
	char	*var_name;

	single_quotation = 0;
	double_quotation = 0;
	i = 0;
	var_name = NULL;
	while (arg[i])
	{
		if (arg[i] == '\'' && !double_quotation)
			single_quotation = !single_quotation;
		else if (arg[i] == '\"' && !single_quotation)
			double_quotation = !double_quotation;
		if (arg[i] == '$' && !single_quotation)
		{
			var_name = extract_var_name(arg, i);
			return (var_name);
		}
		i++;
	}
	return (NULL);
}

void	expand(t_shell *ms, t_command *cmd_list)
{
	t_command	*cmd;
	char		*var_name;
	char		*value;
	int			i;

	(void)ms;
	cmd = cmd_list;
	while (cmd)
	{
		i = 0;
		while (cmd->argv && cmd->argv[i])
		{
			var_name = process_arg(cmd->argv[i]);
			if (var_name)
			{
				if (ft_strcmp(var_name, "?") == 0)
					value = ft_itoa(ms->last_status);
				else
					value = getenv(var_name);
				free(var_name);
			}
			i++;
		}
		cmd = cmd->next;
	}
}

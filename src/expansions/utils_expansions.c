/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expansions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:17:53 by gbercaco          #+#    #+#             */
/*   Updated: 2025/12/02 15:44:59 by gbercaco         ###   ########.fr       */
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

char	*get_variable_value(t_shell *ms, char *var_name)
{
	char	*value;

	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(ms->last_status));
	value = getenv(var_name);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

char	*replace_var_in_arg(char *arg, char *var_name, char *value)
{
	int		var_len;
	char	*before;
	char	*after;
	char	*tmp;
	char	*final;
	int		pos;

	var_len = ft_strlen(var_name);
	pos = 0;
	while (arg[pos] && !(arg[pos] == '$' && ft_strncmp(&arg[pos + 1], var_name,
				var_len) == 0))
		pos++;
	if (arg[pos] == '\0')
		return (ft_strdup(arg));
	before = ft_substr(arg, 0, pos);
	after = ft_strdup(&arg[pos + 1 + var_len]);
	tmp = ft_strjoin(before, value);
	final = ft_strjoin(tmp, after);
	free(before);
	free(after);
	free(tmp);
	return (final);
}

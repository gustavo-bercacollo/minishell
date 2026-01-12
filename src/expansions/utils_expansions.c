/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expansions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:17:53 by gbercaco          #+#    #+#             */
/*   Updated: 2026/01/11 22:19:45 by klima-do         ###   ########.fr       */
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
	t_hash_node	*node;

	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(ms->last_status));
	node = hash_get(ms->env, var_name);
	if (!node || !node->value)
		return (ft_strdup(""));
	return (ft_strdup(node->value));
}

char	*replace_var_in_arg(char *arg, char *var_name, char *value)
{
	int		var_len;
	int		pos;
	char	*final;
	char	*temp;

	var_len = ft_strlen(var_name);
	pos = 0;
	while (arg[pos] && !(arg[pos] == '$' && ft_strncmp(&arg[pos + 1], var_name,
				var_len) == 0))
		pos++;
	if (!arg[pos])
		return (ft_strdup(arg));
	final = ft_substr(arg, 0, pos);
	temp = ft_strjoin(final, value);
	free(final);
	final = temp;
	temp = ft_strjoin(final, &arg[pos + 1 + var_len]);
	free(final);
	return (temp);
}

char	*expand_variable_in_arg(t_shell *ms, char *arg, char *var_name)
{
	char	*value;
	char	*new_arg;

	value = get_variable_value(ms, var_name);
	new_arg = replace_var_in_arg(arg, var_name, value);
	free(value);
	free(var_name);
	return (new_arg);
}

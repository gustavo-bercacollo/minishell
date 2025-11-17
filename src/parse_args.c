/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 17:50:25 by klima-do          #+#    #+#             */
/*   Updated: 2025/11/17 18:35:03 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**parse_args(t_token *token)
{
	int		count;
	t_token	*tmp;
	char	**argv;
	int		i;

	count = 0;
	tmp = token;
	while(tmp)
	{
		if(tmp->type == TOK_WORD)
			count++;
		tmp = tmp->next;
	}
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	i = 0;
	tmp = token;
	while (tmp)
	{
		if (tmp->type == TOK_WORD)
			argv[i++] = ft_strdup(tmp->value);
		tmp = tmp->next;
	}
	argv[i] = NULL;
	return(argv);
}
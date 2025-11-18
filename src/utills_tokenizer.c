/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utills_tokenizer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:56:18 by gbercaco          #+#    #+#             */
/*   Updated: 2025/11/18 19:28:15 by gbercaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_spaces(char **s)
{
	while (**s && (**s == ' ' || **s == '\t'))
		(*s)++;
}

t_token	*new_token(char *value, t_toktype type)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->value = value;
	tok->type = type;
	tok->next = NULL;
	return (tok);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	i;

	dup = malloc(n + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < n && s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

t_token	*read_word(char **s)
{
	char	*start;
	int		len;
	char	*word;

	start = *s;
	len = 0;
	while ((*s)[len] && (*s)[len] != ' ' && (*s)[len] != '\t'
		&& (*s)[len] != '|' && (*s)[len] != '<' && (*s)[len] != '>')
	{
		len++;
	}
	word = ft_strndup(start, len);
	*s += len;
	return (new_token(word, TOK_WORD));
}

t_token	*read_quotes(char **s)
{
	char	quote;
	char	*start;
	int		len;
	char	*word;

	quote = **s;
	(*s)++;
	start = *s;
	len = 0;
	while ((*s)[len] && (*s)[len] != quote)
		len++;
	(*s) += len;
	if (**s == quote)
		(*s)++;
	word = ft_strndup(start, len);
	return (new_token(word, TOK_WORD));
}


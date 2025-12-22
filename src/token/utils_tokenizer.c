/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:56:18 by gbercaco          #+#    #+#             */
/*   Updated: 2025/12/22 20:05:09 by klima-do         ###   ########.fr       */
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

	tok = ft_calloc(1, sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->value = value;
	tok->type = type;
	return (tok);
}

t_token	*read_word(char **s)
{
	char	*start;
	int		len;
	char	*word;
	t_token	*tok;

	start = *s;
	len = 0;
	while ((*s)[len] && (*s)[len] != ' ' && (*s)[len] != '\t'
		&& (*s)[len] != '|' && (*s)[len] != '<' && (*s)[len] != '>')
		len++;
	word = ft_strndup(start, len);
	if (!word)
		return (NULL);
	*s += len;
	tok = new_token(word, TOK_WORD);
	if (!tok)
	{
		free(word);
		return (NULL);
	}
	return (tok);
}

t_token	*read_quotes(char **s)
{
	char	quote;
	char	*start;
	int		len;
	char	*word;
	t_token	*tok;

	quote = **s;
	(*s)++;
	start = *s;
	len = 0;
	while ((*s)[len] && (*s)[len] != quote)
		len++;
	if (!(*s)[len])
	{
		ft_putendl_fd("minishell: syntax error: unclosed quote", 2);
		return (NULL);
	}
	word = ft_strndup(start, len);
	if (!word)
		return (NULL);
	*s += len + 1;
	tok = new_token(word, TOK_WORD);
	if (!tok)
	{
		free(word);
		return (NULL);
	}
	tok->single_quoted = (quote == '\'');
	return (tok);
}

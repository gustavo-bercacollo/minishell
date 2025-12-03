/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 18:30:50 by gbercaco          #+#    #+#             */
/*   Updated: 2025/12/03 18:33:05 by gbercaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_outfile(t_token **tok, t_command *cmd)
{
	if ((*tok)->type == TOK_REDIR_OUT)
		cmd->append = 0;
	else
		cmd->append = 1;
	if (!(*tok)->next)
		return (ft_putendl_fd("minishell: syntax error", 2));
	*tok = (*tok)->next;
	if (cmd->outfile)
		free(cmd->outfile);
	cmd->outfile = ft_strdup((*tok)->value);
}

void	set_infile(t_token **tok, t_command *cmd)
{
	if ((*tok)->type == TOK_HEREDOC)
		cmd->heredoc = 1;
	if (!(*tok)->next)
		return (ft_putendl_fd("minishell: syntax error", 2));
	*tok = (*tok)->next;
	if (cmd->infile)
		free(cmd->infile);
	cmd->infile = ft_strdup((*tok)->value);
}
void	set_heredoc(t_token **tok, t_command *cmd)
{
	int	fd[2];
	char	*line;
	char	*delim;

	if (!(*tok)->next)
		return (ft_putendl_fd("minishell: syntax error near `newline`", 2));
	(*tok) = (*tok)->next;
	delim = (*tok)->value;
	pipe(fd);
	while (1)
	{
		line = readline("heredoc> ");
		if (!line || ft_strcmp(line, delim) == 0)
			break ;
		if (line && *line != '\0')
		{
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
		}
		free(line);
	}
	free(line);
	close(fd[1]);
	cmd->heredoc_fd = fd[0];
	cmd->heredoc = 1;
}

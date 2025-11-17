#ifndef MINI_SHELL_H
#define MINI_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef enum e_toktype
{
	TOK_WORD,
	TOK_PIPE,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_REDIR_APPEND,
	TOK_HEREDOC
}	t_toktype;

typedef struct s_token
{
	char			*value;
	t_toktype		type;
	struct s_token	*list;
}	t_token;


typedef struct t_shell
{
	char	**envp;
	char	*input;
	int		last_status;
	t_token	*tokens;
}	t_shell;

/* Tokenizer */
t_token *tokenize(char *input);

/* Parser */
void    parser(t_shell *ms);

/* Exec */
void    executor(t_shell *ms);

/* Utils */
void    free_tokens(t_token *list);

#endif

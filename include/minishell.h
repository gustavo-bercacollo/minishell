#ifndef MINI_SHELL_H
#define MINI_SHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <curses.h>
#include <term.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"

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
    char            *value;
    t_toktype       type;
    struct s_token  *next;
}   t_token;

typedef struct s_command
{
    char 	**argv;
    char 	*infile;
    char 	*outfile;
    int  	append;
    int  	heredoc;
    int	heredoc_fd;
    struct 	s_command *next;
}   t_command;

typedef struct t_shell
{
	char	**envp;
	char	*input;
	int		last_status;
	t_token	*tokens;
}	t_shell;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

/* Tokenizer */
t_token *tokenize(char *comand);

int	builtin_echo(char **argv);

/* Parser */
t_command	*parse(t_token *tok);

/* Execute */
int	execute_single(t_shell *ms, t_command *cmd);
int	execute_pipe(t_shell *ms, t_command *cmd);

/* Utils Execute */
void	exec_child(t_shell *ms, t_command *cmd);
int	exec_parent(t_shell *ms, pid_t pid);
void	run_child_with_pipe(t_shell *ms, t_command *cmd, int fd_in, int fd[2]);
void	handle_parent_after_fork(int *fd_in, int fd[2], t_command *cmd,
		t_shell *ms, pid_t pid);
	
/* Redirections */
void	handle_outfile(t_command *cmd);
void	handle_infile(t_command *cmd);

/* Utils Tokenizer*/
void	skip_spaces(char **s);
t_token	*new_token(char *value, t_toktype type);
t_token	*read_word(char **s);
t_token	*read_quotes(char **s);
t_token	*read_operator(char **s);

/* Utils Tokenizer*/
t_command	*new_command(void);
void	add_arg(t_command *cmd, char *word);

/* Utils */
void    free_tokens(t_token *list);
char	*get_path_prompt(void);
char	*get_path(char **envp, char *cmd);

#endif

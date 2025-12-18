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

extern int g_interrupted;

typedef enum e_toktype
{
	TOK_WORD,
	TOK_PIPE,
	TOK_AND,
	TOK_OR,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_REDIR_APPEND,
	TOK_HEREDOC
}	t_toktype;


typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE,
	NODE_AND,
	NODE_OR
}	t_node_type;


typedef struct s_ast
{
	t_node_type		type;
	struct s_ast 	*left;
	struct s_ast	*right;
	t_command		*cmd;
}	t_ast;

typedef struct s_token
{
	char				*value;
	t_toktype			type;
	int	single_quoted;
	struct s_token		*next;
}	t_token;

typedef struct s_command
{
	char	**argv;
	char	*infile;
	char	*outfile;
	int	append;
	int	heredoc;
	int	heredoc_fd;
	int	*quoted;
	int	argc;
	struct	s_command *next;
}	t_command;

typedef struct t_shell
{
	char	**envp;
	char	*input;
	int		last_status;
	t_token	*tokens;
}	t_shell;

typedef struct s_heredoc
{
	char	*line;
	int	fd[2];
	int	saved_stdin;
	char	*delim;
	t_command	*cmd;
}	t_heredoc;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

/* Tokenizer */
t_token *tokenize(char *comand);

/* Builtins */
int	builtin_echo(char **argv);

/* Utils Builtins */
int	is_builtin(const char *cmd);
int	execute_builtin(t_shell *ms, t_command *cmd);

/* Parser */
t_command	*parse_cmd(t_token **tok);

/* Setters */
void	set_outfile(t_token **tok, t_command *cmd);
void	set_infile(t_token **tok, t_command *cmd);
void	set_heredoc(t_token **tok, t_command *cmd);

/* Execute */
int	execute(t_shell *ms, t_command *cmd);

/* Utils Execute */
void	exec_child(t_shell *ms, t_command *cmd);
void	run_child(t_shell *ms, t_command *cmd, int fd_in, int fd[2]);
void	wait_child_and_update_status(pid_t pid, t_shell *ms);
void	handle_pipe_parent(int *fd_in, int fd[2], t_command *cmd);

/* Redirections */
void	handle_outfile(t_command *cmd);
void	handle_infile(t_command *cmd);
void	handle_heredoc(t_command *cmd);
void	handle_pipe_input(int fd_in);
void	handle_pipe_output(int fd[2]);

/* Utils Tokenizer*/
void	skip_spaces(char **s);
t_token	*new_token(char *value, t_toktype type);
t_token	*read_word(char **s);
t_token	*read_quotes(char **s);
t_token	*read_operator(char **s);

/* Utils Tokenizer*/
t_command	*new_command(void);
void add_arg(t_command *cmd, t_token *tok);

/* Expansions */
void	expand(t_shell *ms, t_command *cmd_list);

/* Utils Expansions */
char	*process_arg(char *arg);
char	*get_variable_value(t_shell *ms, char *var_name);
char	*replace_var_in_arg(char *arg, char *var_name, char *value);
char	*expand_variable_in_arg(t_shell *ms, char *arg, char *var_name);

/* Signals */
void	sigint_handler(int sig);
void	init_signals(void);
void	set_default_signals_for_child(void);

/* Free */
void	free_tokens(t_token **tokens);
void	free_parse(t_command **cmd);

/* Utils */
char	*get_path_prompt(void);
char	*get_path(char **envp, char *cmd);

#endif

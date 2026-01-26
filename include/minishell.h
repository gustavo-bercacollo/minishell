/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 00:00:00 by klima-do          #+#    #+#             */
/*   Updated: 2026/01/26 18:55:32 by gbercaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define GREEN       "\033[32m"
#define DARK_GREEN  "\033[32;2m"
#define RESET       "\033[0m"

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <errno.h>
# include <string.h>
# include <dirent.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <curses.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "../libft/hash/hash.h"

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

typedef struct s_command
{
	char				**argv;
	char				*infile;
	char				*outfile;
	int					append;
	int					heredoc;
	int					heredoc_fd;
	int					*quoted;
	int					argc;
	struct s_command	*next;
}	t_command;

typedef struct s_hash_env
{
	char				*key;
	char				*value;
	struct s_hash_env	*next;
}	t_hash_env;

typedef struct s_token
{
	char			*value;
	t_toktype		type;
	int				single_quoted;
	struct s_token	*next;
}	t_token;

typedef struct s_ast
{
	t_node_type		type;
	t_token			*token;
	t_command		*cmd;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef struct t_shell
{
	t_hash	*env;
	char	*input;
	int		last_status;
	int		should_exit;
	int		exit_status;
	t_token	*tokens;
}	t_shell;

typedef struct s_heredoc
{
	char		*line;
	int			fd[2];
	int			saved_stdin;
	char		*delim;
	t_command	*cmd;
}	t_heredoc;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

t_token		*tokenize(char *comand);
int			builtin_echo(char **argv);
void		free_dictionary(char *key, char *value);
int			biultin_envp(char **envp);
t_hash		*env_hash_init(char **env);
void		free_hash(t_hash *hash);
int			is_builtin(const char *cmd);
int			execute_builtin(t_shell *ms, t_command *cmd);
int			builtin_cd(t_shell *ms, char **argv);
int			biultin_env(t_hash *env);
int			builtin_exit(t_shell *ms, char **argv);
int			builtin_export(t_shell *ms, char **argv);
int			builtin_pwd(void);
void		biutin_unset(t_shell *sh, char **argv);
t_command	*parse_cmd(t_token **tok);
t_ast		*parse_pipe(t_token **tok);
t_ast		*parser_and_or(t_token **tok);
t_ast		*parse_ast(t_token **tok);
t_ast		*new_ast_node(t_node_type type, t_ast *left, t_ast *right);
t_ast		*ast_from_cmd(t_command *cmd);
void		set_outfile(t_token **tok, t_command *cmd);
void		set_infile(t_token **tok, t_command *cmd);
void		set_heredoc(t_token **tok, t_command *cmd);
int			execute_node(t_shell *ms, t_ast *node);
int			execute_cmd(t_shell *ms, t_ast *node);
int			execute_pipe(t_shell *ms, t_ast *node);
int			execute_or(t_shell *ms, t_ast *node);
int			execute_and(t_shell *ms, t_ast *node);
void		free_envp(char **envp);
char		**hash_to_envp(t_hash *hash);
void		exec_child(t_shell *ms, t_command *cmd);
void		run_child(t_shell *ms, t_command *cmd, int fd_in, int fd[2]);
void		wait_child_and_update_status(pid_t pid, t_shell *ms);
void		handle_pipe_parent(int *fd_in, int fd[2], t_command *cmd);
char		*hash_get_value(t_hash *hash, char *key);
void		handle_outfile(t_command *cmd);
void		handle_infile(t_command *cmd);
void		handle_heredoc(t_command *cmd);
void		handle_pipe_input(int fd_in);
void		handle_pipe_output(int fd[2]);
int			apply_redirections(t_command *cmd);
void		skip_spaces(char **s);
t_token		*new_token(char *value, t_toktype type);
t_token		*read_word(char **s);
t_token		*read_quotes(char **s);
t_token		*read_operator(char **s);
t_command	*new_command(void);
void		add_arg(t_command *cmd, t_token *tok);
void		expand_cmd(t_shell *ms, t_command *cmd);
void		expand_ast(t_shell *ms, t_ast *node);
char		*process_arg(char *arg);
char		*get_variable_value(t_shell *ms, char *var_name);
char		*replace_var_in_arg(char *arg, char *var_name, char *value);
char		*expand_variable_in_arg(t_shell *ms, char *arg, char *var_name);
void		set_signals_interactive(void);
void		set_signals_noninteractive(void);
void		set_signals_child(void);
void		free_tokens(t_token **tokens);
void		free_ast(t_ast *node);
void		free_command(t_command *cmd);
void		free_token(t_token *token);
char		*get_path_prompt(void);
char		*get_path(t_hash *env, char *cmd);
int			compare_nodes(const void *a, const void *b);
void		collect_nodes(t_hash *hash, t_hash_node **nodes);
void		print_export_sorted(t_hash *hash);
char		*search_in_dirs(char **dirs, char *cmd);
char		*check_path_in_dir(char *dir, char *cmd);
char		*hash_get_value(t_hash *hash, char *key);
char		*find_env_path(char **envp);
void		debug_env(t_hash *env);
void		print_banner(void);

#endif

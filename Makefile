# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/17 15:37:39 by klima-do          #+#    #+#              #
#    Updated: 2026/01/26 18:48:26 by gbercaco         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -I include -I libft
LDFLAGS = -L libft -lft
LOGS = valgrind.log norminette.log

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = src/main.c \
	src/utils/get_prompt_path.c \
	src/utils/get_path.c \
	src/utils/path_search.c \
	src/utils/env_utils.c \
	src/utils/hash_utils.c \
	src/utils/banner.c \
	src/token/tokenizer.c \
	src/token/utils_tokenizer.c \
	src/token/read_operators.c \
	src/token/free_tokens.c \
	src/parser/setters.c \
	src/parser/add_argments.c \
	src/parser/utils_parse.c \
	src/parser/free_parse.c \
	src/execute/execute.c \
	src/execute/child.c \
	src/execute/parent.c \
	src/execute/utils_envp_hash.c \
	src/redirections/redirections.c \
	src/redirections/redir_in.c  \
	src/redirections/redir_out.c  \
	src/redirections/redir_pipe.c  \
	src/expansions/expansions.c \
	src/expansions/utils_expansions.c \
	src/signals/signals.c \
	src/execute/execute_and.c\
	src/execute/execute_cmd.c\
	src/execute/execute_or.c\
	src/execute/execute_pipes.c\
	src/parser/ast_from_cmd.c\
	src/parser/new_ast_cmd.c\
	src/parser/parse_cmd.c\
	src/parser/parse_pipe.c\
	src/parser/parse_and_or.c\
	src/parser/parse_ast.c\
	src/env/env.c \
	src/env/free_hash.c \
	src/builtins/builtin_cd.c \
	src/builtins/builtin_echo.c \
	src/builtins/builtin_env.c \
	src/builtins/builtin_exit.c \
	src/builtins/builtin_pwd.c \
	src/builtins/builtin_unset.c \
	src/builtins/utils_builtins.c \
	src/builtins/builtin_export.c \
	src/builtins/builtin_export_utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -lreadline -o $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME) $(LOGS)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

valgrind: $(NAME)
	@valgrind \
	--leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	--track-fds=yes \
	--trace-children=yes \
	--log-file=valgrind.log \
	--suppressions=readline.supp \
	./$(NAME) || true


norminette:
	@norminette ./src > ./norminette.log || true

.PHONY: all clean fclean re

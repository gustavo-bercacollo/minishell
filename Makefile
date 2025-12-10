# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbercaco <gbercaco@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/17 15:37:39 by klima-do          #+#    #+#              #
#    Updated: 2025/12/09 20:25:36 by gbercaco         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -I include -I libft
LDFLAGS = -L libft -lft

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = src/main.c \
	src/builtins/builtin_echo.c \
	src/builtins/utils_builtins.c \
	src/utils/get_prompt_path.c \
	src/utils/get_path.c \
	src/token/tokenizer.c \
	src/token/utils_tokenizer.c \
	src/token/read_operators.c \
	src/token/free_tokens.c \
	src/parser/parse.c \
	src/parser/setters.c \
	src/parser/add_argments.c \
	src/parser/utils_parse.c \
	src/parser/free_parse.c \
	src/execute/execute.c \
	src/execute/child.c \
	src/execute/parent.c \
	src/redirections/redirections.c \
	src/expansions/expansions.c \
	src/expansions/utils_expansions.c \
	src/signals/signals.c 
	
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -lreadline -o $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

valgrind: $(NAME)
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --log-file=valgrind.log --trace-children=yes -s --suppressions=readline.supp ./$(NAME)

.PHONY: all clean fclean re

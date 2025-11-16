# **************************************************************************** #
#                                   CONFIG                                      #
# **************************************************************************** #

NAME        := minishell

CC          := gcc
CFLAGS      := -Wall -Wextra -Werror -Iinclude -I42_libft/include
LDFLAGS     := -L42_libft -lft -lreadline

SRC_DIR     := src
OBJ_DIR     := obj

# LISTE MANUALMENTE OS .c AQUI
SRC         := \
	$(SRC_DIR)/main.c

OBJ         := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# **************************************************************************** #
#                                   RULES                                       #
# **************************************************************************** #

all: $(NAME)

$(NAME): libft $(OBJ_DIR) $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)
	@echo "Minishell compilado! 🐚"

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# **************************************************************************** #
#                                   LIBFT                                       #
# **************************************************************************** #

libft:
	@$(MAKE) -C 42_libft

# **************************************************************************** #
#                                   CLEAN                                        #
# **************************************************************************** #

clean:
	rm -rf $(OBJ_DIR)
	@$(MAKE) -C 42_libft clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C 42_libft fclean

re: fclean all

.PHONY: all clean fclean re libft

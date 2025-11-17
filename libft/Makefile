NAME = libft.a

# Diretórios
LIST_DIR = list
MEM_DIR = memory
STR_DIR = strings
NUM_DIR = number
PRINT_DIR = print
ASCII_DIR = ascii
STACK_DIR = stack
BONUS_SRCS = \
	$(LIST_DIR)/ft_lstadd_back_bonus.c \
	$(LIST_DIR)/ft_lstadd_front_bonus.c \
	$(LIST_DIR)/ft_lstclear_bonus.c \
	$(LIST_DIR)/ft_lstdelone_bonus.c \
	$(LIST_DIR)/ft_lstiter_bonus.c \
	$(LIST_DIR)/ft_lstlast_bonus.c \
	$(LIST_DIR)/ft_lstnew_bonus.c \
	$(LIST_DIR)/ft_lstsize_bonus.c \
	$(LIST_DIR)/ft_lstmap_bonus.c

SRCS = \
	$(NUM_DIR)/ft_atoi.c \
	$(NUM_DIR)/ft_itoa.c \
	$(NUM_DIR)/ft_atol.c\
	$(MEM_DIR)/ft_memset.c \
	$(MEM_DIR)/ft_bzero.c \
	$(MEM_DIR)/ft_memcpy.c \
	$(MEM_DIR)/ft_memmove.c \
	$(MEM_DIR)/ft_memchr.c \
	$(MEM_DIR)/ft_memcmp.c \
	$(MEM_DIR)/ft_calloc.c \
	$(STR_DIR)/ft_strlen.c \
	$(STR_DIR)/ft_strlcpy.c \
	$(STR_DIR)/ft_strlcat.c \
	$(STR_DIR)/ft_strchr.c \
	$(STR_DIR)/ft_strrchr.c \
	$(STR_DIR)/ft_strncmp.c \
	$(STR_DIR)/ft_strnstr.c \
	$(STR_DIR)/ft_strdup.c \
	$(STR_DIR)/ft_substr.c \
	$(STR_DIR)/ft_strjoin.c \
	$(STR_DIR)/ft_strtrim.c \
	$(STR_DIR)/ft_split.c \
	$(STR_DIR)/ft_strmapi.c \
	$(STR_DIR)/ft_striteri.c \
	$(STR_DIR)/ft_toupper.c \
	$(STR_DIR)/ft_tolower.c \
	$(STR_DIR)/get_next_line.c\
	$(PRINT_DIR)/ft_putchar_fd.c \
	$(PRINT_DIR)/ft_putstr_fd.c \
	$(PRINT_DIR)/ft_putendl_fd.c \
	$(PRINT_DIR)/ft_putnbr_fd.c \
	$(ASCII_DIR)/ft_isalpha.c \
	$(ASCII_DIR)/ft_isdigit.c \
	$(ASCII_DIR)/ft_isalnum.c \
	$(ASCII_DIR)/ft_isascii.c \
	$(ASCII_DIR)/ft_isprint.c\
	$(STACK_DIR)/pop.c\
	$(STACK_DIR)/push.c\
	$(STACK_DIR)/init_stack.c\
	$(STACK_DIR)/stack_clear.c\
	$(STACK_DIR)/find_last.c\
	manage_memory/ft_free_split.c

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
CC = cc
CFLAGS = -Wall -Wextra -Werror -I.


all: $(NAME)

$(NAME): $(OBJS)
	@echo "📦 Compilando arquivos obrigatórios..."
	@ar rcs $(NAME) $(OBJS)
	@echo "✅ Todos os arquivos foram compilados com sucesso!"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

bonus: .bonus_build

.bonus_build: $(OBJS) $(BONUS_OBJS)
	@echo "📦 Compilando arquivos bônus e obrigatórios..."
	@ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)
	@touch .bonus_build
	@echo "✅ Todos os arquivos foram compilados com sucesso!"

clean:
	@rm -f $(OBJS)
	@rm -f $(BONUS_OBJS)
	@rm -f .bonus_build

fclean: clean
	@rm -f $(NAME)
	@echo "❗Todos os arquivos foram removidos com sucesso!"

re: fclean all

.PHONY: all clean fclean re bonus

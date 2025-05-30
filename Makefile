NAME		= minishell

INC_DIR		= inc
LIB_DIR		= lib
SRC_DIR		= src
BUILD_DIR	= build

LIBFT_DIR	= $(LIB_DIR)/libft
LIBFT		= $(LIBFT_DIR)/libft.a

CFLAGS		= -I$(INC_DIR) -I$(LIBFT_DIR) # -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR)
LDFLAGS		= -L$(LIBFT_DIR)
LDLIBS		= -lreadline -lft
RM			= rm -rf

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	CFLAGS	+= -I/opt/homebrew/opt/readline/include
	LDFLAGS	+= -L/opt/homebrew/opt/readline/lib
	LDLIBS	+= -lcurses
endif

VPATH		= src:src/env:src/exec:src/builtin:src/utils:src/helpers:src/parser:src/tokenizer:src/expander
SRCS		= main.c \
			str_utils.c exit_utils.c \
			env_helpers.c env_utils.c env_init.c \
			exec.c exec_utils.c exec_prep.c exec_redir.c exec_builtin.c \
			echo.c export.c pwd.c unset.c env.c cd.c \
			expander_utils.c expander.c \
			debug_funcs.c quote_checker.c split_expanded_tokens_utils.c merge_tokens.c  split_expanded_tokens.c  split_first_token.c \
			heredoc.c  parser.c  parser_init.c \
			tokenizer.c  tokenizer_helpers.c  tokenizer_utils.c
OBJS		= $(addprefix $(BUILD_DIR)/,$(SRCS:.c=.o))

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)

clean:
	$(RM) $(BUILD_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME) 
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
NAME		= minishell

INC_DIR		= inc
LIB_DIR		= lib
SRC_DIR		= src
BUILD_DIR	= build

LIBFT_DIR	= $(LIB_DIR)/libft
LIBFT		= $(LIBFT_DIR)/libft.a

CFLAGS		= -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR)
LDFLAGS		= -L$(LIBFT_DIR)
LDLIBS		= -lreadline -lft
RM			= rm -rf

# kutaycim special
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	CFLAGS	+= -I/opt/homebrew/opt/readline/include
	LDFLAGS	+= -L/opt/homebrew/opt/readline/lib
	LDLIBS	+= -lcurses
endif

VPATH		= src
SRCS		= 	main.c \
			signals.c \
			expander.c \
			helper.c \
			quote_checker.c \
			tokenizer.c \
			merge_tokens.c \
			parser.c \
			split_expanded_tokens.c \
			parser_init.c \
			expander_utils.c \
			split_expanded_tokens_utils.c \
			tokenizer_utils.c \
			tokenizer_helpers.c
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

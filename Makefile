NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -I/opt/homebrew/opt/readline/include \
		 -Ilibft
LDFLAGS = -L/opt/homebrew/opt/readline/lib libft/libft.a
RLFLAGS = -lreadline -lcurses

SRCS = 	main.c \
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
		tokenizer_helpers.c \
		

OBJS = $(SRCS:.c=.o)

HEADER = minishell.h

LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS) $(RLFLAGS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -I/opt/homebrew/opt/readline/include \
		 -Ilibft -Ift_printf
LDFLAGS = -L/opt/homebrew/opt/readline/lib libft/libft.a ft_printf/ft_printf.a
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
		
OBJS = $(SRCS:.c=.o)

HEADER = minishell.h

LIBFT_DIR = libft
FT_PRINTF_DIR = ft_printf

LIBFT = $(LIBFT_DIR)/libft.a
FT_PRINTF = $(FT_PRINTF_DIR)/ft_printf.a

all: $(LIBFT) $(FT_PRINTF) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME) $(OBJS) $(RLFLAGS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(FT_PRINTF):
	make -C $(FT_PRINTF_DIR)

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT_DIR)
	make clean -C $(FT_PRINTF_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(FT_PRINTF_DIR)

re: fclean all

.PHONY: all clean fclean re

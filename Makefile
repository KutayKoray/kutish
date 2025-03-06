NAME		= minishell

CFLAGS		= -Wall -Wextra -Werror
LDLIBS		= -lreadline
RM			= rm -rf

PRINTF_DIR	= ft_printf
PRINTF_LIB	= $(PRINTF_DIR)/ft_printf.a

LIBFT_DIR	= libft
LIBFT_LIB	= $(LIBFT_DIR)/libft.a

BUILD_DIR	= build
VPATH		= src
SRCS		= main.c tokenizer.c utils.c expander.c
OBJS		= $(addprefix $(BUILD_DIR)/,$(SRCS:.c=.o))

all: $(PRINTF_LIB) $(LIBFT_LIB) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDLIBS) $(PRINTF_LIB) $(LIBFT_LIB)

$(PRINTF_LIB):
	make -C $(PRINTF_DIR)

$(LIBFT_LIB):
	make -C $(LIBFT_DIR)

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(BUILD_DIR)
	make -C $(PRINTF_DIR) clean
	make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(PRINTF_DIR) fclean
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

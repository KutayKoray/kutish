SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
       ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
       ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
       ft_calloc.c ft_strdup.c ft_toupper.c ft_tolower.c \
       ft_strchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c \
       ft_strnstr.c ft_atoi.c ft_strrchr.c ft_substr.c \
       ft_strjoin.c ft_strtrim.c ft_split.c \
       ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
       ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
SRCSB = ft_lstnew.c ft_lstadd_front.c \
	ft_lstsize.c ft_lstlast.c \
	ft_lstadd_back.c ft_lstdelone.c \
	ft_lstclear.c ft_lstiter.c \
	ft_lstmap.c
OBJS = ${SRCS:.c=.o}
OBJSB = ${SRCSB:.c=.o}
NAME = libft.a
LIBC = ar rcs -v
CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror
IS_BONUS = .is_bonus

${NAME}: ${OBJS}
	${LIBC} ${NAME} ${OBJS}

${IS_BONUS}: ${OBJSB}
	${LIBC} ${NAME} ${OBJSB}
	mkdir ${IS_BONUS}

bonus: ${IS_BONUS}
	
all: ${NAME}

clean:
	${RM} ${OBJS} ${OBJSB} ${IS_BONUS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all bonus clean fclean re
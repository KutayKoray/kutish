#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

extern int	g_exit_status;

char		*expand_input(const char *input);

void		init_signals(void);

char		*strappend_char(char *str, char c);
char		*strappend_str(char *str, const char *suffix);
char		*ft_itoa(int n);
char		*quote_trimmer(const char *input);

int			ft_isalnum(int c);
int			quote_checker(const char *input);


#endif

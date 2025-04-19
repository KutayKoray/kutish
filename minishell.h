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

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIN,
	T_REDOUT,
	T_APPEND,
	T_HEREDOC
}					t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	int				joined;
	struct s_token	*next;
}					t_token;

extern int			g_exit_status;

void				init_signals(void);
void				expand_token_list(t_token *tokens);
void				expand_token_list(t_token *tokens);
void				trim_token_quotes(t_token *tokens);
void				free_token_list(t_token *tokens);
void				trim_token_quotes(t_token *tokens);
void				merge_joined_tokens(t_token **tokens);

char				*expand_input(const char *input);
char				*strappend_char(char *str, char c);
char				*strappend_str(char *str, const char *suffix);
char				*ft_itoa(int n);
char				*quote_trimmer(const char *input);

int					ft_isalnum(int c);
int					quote_checker(const char *input);

t_token				*tokenize(const char *input);

#endif

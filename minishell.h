/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoray <kkoray@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:32:46 by kkoray            #+#    #+#             */
/*   Updated: 2025/04/26 12:32:47 by kkoray           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_printf/ft_printf.h"
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

typedef struct s_expand_ctx
{
	char			*result;
	int				in_single_quote;
	int				in_double_quote;
}	t_expand_ctx;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	int				joined;
	struct s_token	*next;
}					t_token;

typedef struct s_token_ctx
{
	t_token			**head;
	int				joined;
}					t_token_ctx;

typedef struct s_cmd
{
	char			**argv;
	char			**outfiles;
	char			*infile;
	char			*heredoc_eof;
	int				append;
	int				is_heredoc;
	struct s_cmd	*next;
}					t_cmd;

extern int			g_exit_status;

void				init_signals(void);
void				expand_token_list(t_token *tokens);
void				trim_token_quotes(t_token *tokens);
void				free_token_list(t_token *tokens);
void				trim_token_quotes(t_token *tokens);
void				merge_joined_tokens(t_token **tokens);
void				print_cmd_list(t_cmd *cmd);
void				split_expanded_tokens(t_token **head);
void				ft_free_strarray(char **arr);
void				add_token(t_token **head, char *value, t_token_type type,
						int joined);

char				*expand_input(const char *input);
char				*strappend_char(char *str, char c);
char				*strappend_str(char *str, const char *suffix);
char				*quote_trimmer(const char *input);
char				*get_env_value(const char *key);
char				*ft_strndup(const char *s, size_t n);

int					ft_isalnum(int c);
int					quote_checker(const char *input);
int					read_quoted(const char *str, int start, char quote);
int					is_operator_char(char c);
int					read_plain(const char *str, int start);
int					operator_length(const char *s);
int					skip_space(const char *input, int i, int *prev_was_space);

t_token				*tokenize(const char *input);
t_token				*create_token(const char *value, t_token_type type,
						int joined);

t_token_type		get_operator_type(const char *s);

t_cmd				*parse_tokens(t_token *tokens);
t_cmd				*create_cmd(void);

size_t				get_env_key_len(const char *str, size_t *i);

#endif

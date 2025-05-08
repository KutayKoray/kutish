/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:32:46 by kkoray            #+#    #+#             */
/*   Updated: 2025/05/08 23:00:11 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

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
	int				trimmed;
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
	char			**heredoc_eof;
	char			*heredoc_buffer;
	int				append;
	int				is_heredoc;
	int				heredoc_expand;
	struct s_cmd	*next;
}					t_cmd;

extern int			g_exit_status;

void				init_signals(void);
void				expand_token_list(t_token *tokens);
void				trim_token_quotes(t_token *tokens);
void				free_token_list(t_token *tokens);
void				free_cmd_list(t_cmd *cmds);
void				trim_token_quotes(t_token *tokens);
void				merge_joined_tokens(t_token **tokens);
void				split_expanded_tokens(t_token **head);
void				ft_free_strarray(char **arr);
void				add_token(t_token **head, char *value, t_token_type type,
						int joined);
void				add_heredoc(char ***heredocs, const char *value);

char				*expand_input(const char *input);
char				*strappend_char(char *str, char c);
char				*strappend_str(char *str, const char *suffix);
char				*get_env_value(const char *key);
char				*ft_strndup(const char *s, size_t n);
char				*get_heredoc(t_cmd *cmd);

int					quote_checker(const char *input);
int					read_quoted(const char *str, int start, char quote);
int					is_operator_char(char c);
int					read_plain(const char *str, int start);
int					operator_length(const char *s);
int					skip_space(const char *input, int i, int *prev_was_space);
int					ft_strcmp(const char *s1, const char *s2);

t_token				*tokenize(const char *input);
t_token				*create_token(const char *value, t_token_type type,
						int joined, int trimmed);

t_token_type		get_operator_type(const char *s);

t_cmd				*parse_tokens(t_token *tokens);
t_cmd				*create_cmd(void);

size_t				get_env_key_len(const char *str, size_t *i);

#endif

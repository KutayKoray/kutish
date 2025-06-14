/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:04:47 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/06/14 12:00:16 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>

# define SHELL_NAME "kutish"
# define PROMPT "\e[0;34m☁  \e[1;36mkutish\e[0m "

# define EXECUTION_SUCCESS 0
# define EXECUTION_FAILURE 1
# define SYNTAX_ERROR 2
# define EX_NOEXEC 126
# define EX_NOTFOUND 127

extern int	g_signal;

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
	int				trimmed;
	int				expanded;
	struct s_token	*next;
}					t_token;

typedef struct s_token_ctx
{
	t_token			**head;
	int				joined;
}					t_token_ctx;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_expand_ctx
{
	char	*result;
	int		expanded;
	int		in_single_quote;
	int		in_double_quote;
	char	first_quote;
	t_env	*env;
}	t_expand_ctx;

typedef struct	s_pipe_info
{
	int		pipe_fd[2];
	int		fd_in;
	int		original_stdin;
	int		original_stdout;
}	t_pipe_info;

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

// builtin
int				echo_builtin(char **argv);
int				export_builtin(char **argv, t_env **env);
int				unset_builtin(char **argv, t_env **env);
int				pwd_builtin(void);
int				env_builtin(t_env *env);
int				cd_builtin(char **argv, t_env **env);
int				exit_builtin(t_cmd *cmd);

// env.c
t_env			*init_env_list(char **envp);
int				set_env(t_env **env, char *key, char *value);
int				unset_env(t_env **env, char *key);
char			*get_env_value(t_env *env, char *key);
int				is_valid_key(char *key);
int				append_env_node(t_env **env, char *key, char *value);
void			free_env_list(t_env *env);
void			initialize_envs(t_env **env);

// exec
void			execute_pipeline(t_cmd *cmd, t_env **env);
int				create_pipe(int *fd);
int				is_builtin(char *cmd);
void			wait_for_pipeline(pid_t last_pid);
char			*get_cmd_path(t_cmd *cmd, t_env *env);
char			**env2envp(t_env *env);
int				infile_redirection(t_cmd *cmd, t_pipe_info *pipe_info);
int				outfile_redirection(t_cmd *cmd);
void			handle_builtin(t_cmd *cmd, t_env **env);
int				handle_single_builtin(t_cmd *cmd, t_env **env, t_pipe_info *pipe_info);
int				*exit_status(void);
void			exit_with_error(int status, const char *message, int is_exit);
t_cmd			**get_cmd_head(t_cmd *cmd);
t_env			**get_env_head(t_env *env);
void			free_lists(void);

// expander
char			*expand_variable(t_expand_ctx *ctx, const char *str, size_t *i);
void			handle_tilde(const char *input, size_t *i, t_expand_ctx *ctx);
void			handle_quotes(const char *input, size_t *i, t_expand_ctx *ctx);
void			handle_dollar(const char *input, size_t *i, t_expand_ctx *ctx);
void			expand_token_list(t_token *tokens, t_env *env);
char			*char_to_str(char c);
size_t			get_env_key_len(const char *str, size_t *i);

// parser
t_cmd			*parse_tokens(t_token *tokens, t_env *env);
void			assign_heredoc_buffers(t_cmd *cmds, t_env *env);
void			free_cmd_list(t_cmd *cmds);
char			*expand_input(const char *input, t_token *token, t_env *env);
void			add_heredoc(char ***heredoc_eof, const char *value);
t_cmd			*create_cmd(void);

// signals
void			set_signal_handler(int type);
void			prompt_handler(int signum);
void			sigquit_handler(int signum);
void			execute_handler(int signum);
void			heredoc_handler(int signum);

// tokenizer
t_token			*tokenize(const char *input);
void			free_token_list(t_token *tokens);
int				operator_length(const char *s);
int				skip_space(const char *input, int i, int *prev_was_space);
int				is_operator_char(char c);
t_token_type	get_operator_type(const char *s);
void			add_token(t_token **head, char *value, t_token_type type, int joined);
int				read_word(const char *str, int start);
void			split_expanded_tokens(t_token **head);
void	 		trim_token_quotes(t_token *tokens);

// utils
char			*str_arr_join(char **arr, char *sep);
void			free_str_arr(char **arr);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strndup(const char *s, size_t n);
int				is_valid_input(const char *input);
void	 		debug_print_cmd(t_token *tokens, char *msg);
void	 		print_cmd_list(t_cmd *cmd);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoray <kkoray@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:19:58 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/05/29 20:06:51 by kkoray           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "minishell.h"
#include "tokenizer.h"
#include "env.h"
#include "utils.h"

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

t_cmd	*parse_tokens(t_token *tokens);
void	assign_heredoc_buffers(t_cmd *cmds, t_env *env);
void	free_cmd_list(t_cmd *cmds);
char	*expand_input(const char *input, t_env *env);
void	add_heredoc(char ***heredoc_eof, const char *value);
t_cmd	*create_cmd(void);

#endif
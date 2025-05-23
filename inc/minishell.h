/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:04:47 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/05/23 16:06:08 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_cmd
{
	char			**argv;
	char			**outfiles;
	char			*infile;
	char			**heredoc_eof;
	char			*heredoc_buffer;
	int				append;
	int				is_heredoc;
	struct s_cmd	*next;
}					t_cmd;

// utils.c
char	*str_arr_join(char **arr, char *sep);
void	free_str_arr(char **arr);

#endif
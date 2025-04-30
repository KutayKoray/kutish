/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:32:32 by kkoray            #+#    #+#             */
/*   Updated: 2025/05/01 01:44:48 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_exit_status = 0;

static char	*expand_variable(const char *str, size_t *i)
{
	size_t	start;
	size_t	len;
	char	*var;
	char	*value;

	start = ++(*i);
	if (str[start] == '?')
	{
		(*i)++;
		return (ft_itoa(g_exit_status));
	}
	if (!str[start] || !(ft_isalpha(str[start]) || str[start] == '_'))
		return (ft_strdup("$"));
	len = get_env_key_len(str, i);
	var = ft_strndup(str + start, len);
	value = get_env_value(var);
	free(var);
	if (value)
		return (ft_strdup(value));
	else
		return (ft_strdup(""));
}

static void	handle_quotes(const char *input, size_t *i, t_expand_ctx *ctx)
{
	if (input[*i] == '\'' && !ctx->in_double_quote)
	{
		ctx->in_single_quote = !ctx->in_single_quote;
		ctx->result = strappend_char(ctx->result, input[(*i)++]);
	}
	else if (input[*i] == '"' && !ctx->in_single_quote)
	{
		ctx->in_double_quote = !ctx->in_double_quote;
		ctx->result = strappend_char(ctx->result, input[(*i)++]);
	}
}

static void	handle_dollar(const char *input, size_t *i, t_expand_ctx *ctx)
{
	char	*expanded;

	if (ctx->in_single_quote)
		ctx->result = strappend_char(ctx->result, input[(*i)++]);
	else
	{
		expanded = expand_variable(input, i);
		ctx->result = strappend_str(ctx->result, expanded);
		free(expanded);
	}
}

static void	handle_tilde(t_expand_ctx *ctx, size_t *i)
{
	char	*home;
	char	*tmp;
	
	home = get_env_value("HOME");
	if (home && *home)
		// ctx->result = strappend_str(ctx->result, home);
		tmp = strappend_str(ctx->result, home);
	else
		// ctx->result = strappend_char(ctx->result, '~');
		tmp = strappend_char(ctx->result, '~');
	free(ctx->result);
	ctx->result = tmp;
	(*i)++;
}

char	*expand_input(const char *input)
{
	t_expand_ctx	ctx;
	size_t			i;
	char			*tmp;

	ctx.result = calloc(1, 1);
	ctx.in_single_quote = 0;
	ctx.in_double_quote = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
			handle_quotes(input, &i, &ctx);
		else if (input[i] == '$')
			handle_dollar(input, &i, &ctx);
		else if (input[i] == '~')
			handle_tilde(&ctx, &i);
		else
		{
			tmp = strappend_char(ctx.result, input[i]);
			free(ctx.result);
			ctx.result = tmp;
			i++;
		}
	}
	return (ctx.result);
}

void	expand_token_list(t_token *tokens)
{
	t_token	*tmp;
	char	*expanded;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == T_WORD)
		{
			if (tmp->value[0] == '\'' && tmp->value[ft_strlen(tmp->value)
					- 1] == '\'')
			{
				tmp = tmp->next;
				continue ;
			}
			expanded = expand_input(tmp->value);
			free(tmp->value);
			tmp->value = expanded;
		}
		tmp = tmp->next;
	}
}

static char *find_cmd_path(char *cmd)
{
	char	*path;
	char	*tmp;
	char	*env_path;
	char	**paths;
	int		i;

	env_path = get_env_value("PATH");
	if (!env_path)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (NULL);
	paths = ft_split(env_path, ':');
	i = 0;
	while (paths[i])
	{
		tmp = strappend_str(paths[i], "/");
		path = strappend_str(tmp, cmd);
		free(tmp);
		if (!access(path, F_OK))
		{
			i = -1;
			break ;
		}
		free(path);
		i++;
	}
	ft_free_strarray(paths);
	if (i != -1)
		return (NULL);
	return (path);
}

void	expand_cmd_path(t_token **tokens)
{
	t_token	*tmp;
	char	*expanded;
	int		is_first_token;

	tmp = *tokens;
	is_first_token = 1;
	while (tmp)
	{
		if (tmp->type == T_WORD && is_first_token)
		{
			is_first_token = 0;
			expanded = find_cmd_path(tmp->value);
			if (!expanded)
			{
				tmp = tmp->next;
				continue ;
			}
			free(tmp->value);
			tmp->value = expanded;
		}
		tmp = tmp->next;
	}
}
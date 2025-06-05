/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:32:32 by kkoray            #+#    #+#             */
/*   Updated: 2025/06/05 22:35:45 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_variable(t_expand_ctx *ctx, const char *str, size_t *i)
{
	size_t	start;
	size_t	len;
	char	*var;
	char	*value;

	start = ++(*i);
	if (str[start] == '?')
	{
		(*i)++;
		return (ft_itoa(*exit_status()));
	}
	if (!str[start] || !(ft_isalpha(str[start]) || str[start] == '_'))
		return (ft_strdup("$"));
	len = get_env_key_len(str, i);
	var = ft_strndup(str + start, len);
	value = get_env_value(ctx->env, var);
	free(var);
	if (value)
	{
		ctx->expanded = 1;
		return (ft_strdup(value));
	}
	else
		return (ft_strdup(""));
}

static void	handle_quotes(const char *input, size_t *i, t_expand_ctx *ctx)
{
	if (input[*i] == '\'')
	{
		ctx->in_single_quote = !ctx->in_single_quote;
		ctx->result = ft_strjoin(ctx->result, char_to_str(input[(*i)++]));
	}
	else if (input[*i] == '"')
	{
		ctx->in_double_quote = !ctx->in_double_quote;
		ctx->result = ft_strjoin(ctx->result, char_to_str(input[(*i)++]));
	}
}

static void	handle_dollar(const char *input, size_t *i, t_expand_ctx *ctx)
{
	char	*expanded;

	if (ctx->first_quote == '\'')
		ctx->result = ft_strjoin(ctx->result, char_to_str(input[(*i)++]));
	else
	{
		expanded = expand_variable(ctx, input, i);
		ctx->result = ft_strjoin(ctx->result, expanded);
		free(expanded);
	}
}

static void	handle_tilde(const char *input, size_t *i, t_expand_ctx *ctx)
{
	char	*home;
	char	*tmp;

	home = get_env_value(ctx->env, "HOME");
	if (input[*i + 1] || (*i && input[*i - 1]))
		tmp = ft_strjoin(ctx->result, char_to_str(input[*i]));
	else if (home && *home)
		tmp = ft_strjoin(ctx->result, home);
	else
		tmp = ft_strjoin(ctx->result, char_to_str('~'));
	free(ctx->result);
	ctx->result = tmp;
	(*i)++;
}

char	*expand_input(const char *input, t_token *token, t_env *env)
{
	t_expand_ctx	ctx;
	size_t			i;
	char			*tmp;

	ctx.result = calloc(1, 1);
	ctx.expanded = 0;
	ctx.in_single_quote = 0;
	ctx.in_double_quote = 0;
	ctx.env = env;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			handle_quotes(input, &i, &ctx);
		else if (input[i] == '"')
		{
			ctx.first_quote = input[i];
			handle_quotes(input, &i, &ctx);	
		}
		else if (input[i] == '$')
		{
			handle_dollar(input, &i, &ctx);
			if (token && ctx.expanded) // token check for heredoc expansion, we'll pass NULL for it
				token->expanded = 1;
		}
		else if (input[i] == '~')
			handle_tilde(input, &i, &ctx);
		else
		{
			tmp = ft_strjoin(ctx.result, char_to_str(input[i]));
			free(ctx.result);
			ctx.result = tmp;
			i++;
		}
	}
	return (ctx.result);
}

void	expand_token_list(t_token *tokens, t_env *env)
{
	t_token	*cur;
	t_token	*prev;
	char	*expanded;

	cur = tokens;
	prev = NULL;
	while (cur)
	{
		if (cur->type == T_WORD)
		{
			if ((cur->value[0] == '\'' && cur->value[ft_strlen(cur->value) - 1] == '\'') ||
				(prev && prev->type == T_HEREDOC))
			{
				prev = cur;
				cur = cur->next;
				continue ;
			}
			expanded = expand_input(cur->value, cur, env);
			free(cur->value);
			cur->value = expanded;
		}
		prev = cur;
		cur = cur->next;
	}
}

char *char_to_str(char c)
{
    char* str;
	
	str = (char*)malloc(2 * sizeof(char));
    if (!str)
        return NULL;
    str[0] = c;
    str[1] = '\0';
    return str;
}

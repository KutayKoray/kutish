/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:22:44 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/06/16 20:41:45 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

static int	add_env_var(char *env_str, t_env **env)
{
	char	*eq_pos;
	char	*key;
	char	*value;

	eq_pos = ft_strchr(env_str, '=');
	if (!eq_pos)
		return (1);
	key = ft_substr(env_str, 0, eq_pos - env_str);
	value = ft_strdup(eq_pos + 1);
	if (!key || !value || !append_env_node(env, key, value))
	{
		free(key);
		free(value);
		return (0);
	}
	free(key);
	free(value);
	return (1);
}

t_env	*init_env_list(char **envp)
{
	t_env	*env;

	env = NULL;
	if (!envp || !*envp)
		return (NULL);
	while (*envp)
	{
		if (!add_env_var(*envp, &env))
		{
			free_env_list(env);
			return (NULL);
		}
		envp++;
	}
	return (env);
}

int	set_env(t_env **env, char *key, char *value)
{
	t_env	*tmp;
	char	*new_value;

	if (!env || !key)
		return (0);
	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, ft_strlen(key) + 1))
		{
			free(tmp->value);
			if (value)
			{
				new_value = ft_strdup(value);
				if (!new_value)
					return (0);
				tmp->value = new_value;
			}
			else
				tmp->value = NULL;
			return (1);
		}
		tmp = tmp->next;
	}
	return (append_env_node(env, key, value));
}

int	unset_env(t_env **env, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	if (!env || !key)
		return (0);
	tmp = *env;
	prev = NULL;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, ft_strlen(key) + 1))
		{
			if (prev)
				prev->next = tmp->next;
			else
				*env = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return (1);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}

char	*get_env_value(t_env *env, char *key)
{
	t_env	*tmp;

	if (!env || !key)
		return (NULL);
	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, ft_strlen(key) + 1))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

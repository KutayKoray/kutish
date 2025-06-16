/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:20:02 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/06/16 20:35:08 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

int	is_valid_key(char *key)
{
	if (!key || !*key || ft_isdigit(*key))
		return (0);
	while (*key)
	{
		if (!ft_isalnum(*key) && *key != '_')
			return (0);
		key++;
	}
	return (1);
}

static t_env	*create_env_node(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	if (!new->key)
	{
		free(new);
		return (NULL);
	}
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->next = NULL;
	return (new);
}

int	append_env_node(t_env **env, char *key, char *value)
{
	t_env	*new;
	t_env	*current;

	if (!env || !key)
		return (0);
	new = create_env_node(key, value);
	if (!new)
		return (0);
	if (!*env)
	{
		*env = new;
		return (1);
	}
	current = *env;
	while (current->next)
		current = current->next;
	current->next = new;
	return (1);
}

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		if (tmp->key)
			free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

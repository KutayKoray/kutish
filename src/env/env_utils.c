/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:20:02 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/05/28 14:24:29 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks whether a key name is valid for environment use.
 *
 * A valid key must start with a letter or underscore, and contain
 * only alphanumeric characters or underscores.
 *
 * @param key The key to validate.
 * @return int 1 if valid, 0 if invalid.
 */
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

/**
 * @brief Adds a new environment node at the beginning of the list.
 *
 * Allocates a new t_env node, duplicates the key and value strings,
 * and inserts the new node at the head of the linked list.
 * If memory allocation fails at any point, cleans up and returns failure.
 *
 * @param env Pointer to the head pointer of the environment linked list.
 * @param key The key string to duplicate and store in the new node.
 * @param value The value string to duplicate and store in the new node
 * (can be NULL).
 * @return int Returns 1 on success, 0 on failure.
 */
int	append_env_node(t_env **env, char *key, char *value)
{
	t_env	*new;

	if (!env || !key)
		return (0);
	new = malloc(sizeof(t_env));
	if (!new)
		return (0);
	new->key = ft_strdup(key);
	if (!new->key)
		return (free(new), 0);
	if (value)
	{
		new->value = ft_strdup(value);
		if (!new->value)
			return (free(new->key), free(new), 0);
	}
	else
		new->value = NULL;
	new->next = *env;
	*env = new;
	return (1);
}

/**
 * @brief Frees the entire environment list and its contents.
 *
 * Iterates through the list and frees each node's key, value,
 * and the node itself.
 *
 * @param env Pointer to the head of the environment list.
 */
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

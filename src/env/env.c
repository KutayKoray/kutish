/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:22:44 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/05/27 16:41:54 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <stdlib.h>

/**
 * @brief Initializes the environment list from the envp array.
 *
 * Parses each "KEY=VALUE" string in envp, splits it into key and value,
 * and appends each as a node in a linked list of t_env structures.
 *
 * @param envp The environment array passed to main().
 * @return t_env* Pointer to the head of the newly created list,
 * or NULL on error.
 */
t_env	*init_env_list(char **envp)
{
	t_env	*env;
	char	*eq_pos;
	char	*key;
	char	*value;

	if (!envp)
		return (NULL);
	env = NULL;
	while (*envp)
	{
		eq_pos = ft_strchr(*envp, '=');
		key = ft_substr(*envp, 0, eq_pos - *envp);
		value = ft_strdup(eq_pos + 1);
		if (!key || !value || !append_env_node(&env, key, value))
			return (free(key), free(value), free_env_list(env), NULL);
		free(key);
		free(value);
		envp++;
	}
	return (env);
}

/**
 * @brief Sets or updates a variable in the environment list.
 *
 * If the key exists, its value is replaced (with ft_strdup).
 * If the key doesn't exist, a new node is appended.
 * Value can be NULL, in which case the key will have no value.
 *
 * @param env Pointer to the environment list pointer.
 * @param key The key to set or update.
 * @param value The new value, or NULL.
 * @return int 1 on success, 0 on error, -1 on invalid input.
 */
int	set_env(t_env **env, char *key, char *value)
{
	t_env	*tmp;
	char	*new_value;

	if (!env || !key || !is_valid_key(key))
		return (-1);
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

/**
 * @brief Removes a variable from the environment list by key.
 *
 * Frees the corresponding key, value, and node from memory.
 *
 * @param env Pointer to the environment list pointer.
 * @param key The key to remove.
 * @return int 1 if the key was found and removed, 0 otherwise.
 */
int	unset_env(t_env **env, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	if (!env || !*env || !key)
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
			return (free(tmp->key), free(tmp->value), free(tmp), 1);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}

/**
 * @brief Retrieves the value of a key from the environment list.
 *
 * Searches the linked list for the given key and returns its value.
 *
 * @param env Pointer to the environment list.
 * @param key The key to search for.
 * @return char* The value if found, or NULL if not found or invalid input.
 */
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

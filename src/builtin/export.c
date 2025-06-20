/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:35:06 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/06/16 18:03:10 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static void	print_error(char *key)
{
	ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
	ft_putstr_fd(": export: `", STDERR_FILENO);
	ft_putstr_fd(key, STDERR_FILENO);
	ft_putstr_fd("`: not a valid identifier\n", STDERR_FILENO);
}

static void	print_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "_", 2))
		{
			tmp = tmp->next;
			continue ;
		}
		else if (tmp->key && tmp->value)
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		else if (tmp->key)
			printf("declare -x %s\n", tmp->key);
		tmp = tmp->next;
	}
}

static int	parse_key_value(char *arg, char **key, char **value)
{
	char	*eq;

	eq = ft_strchr(arg, '=');
	if (eq)
	{
		*key = ft_substr(arg, 0, eq - arg);
		if (!*key)
			return (0);
		*value = ft_strdup(eq + 1);
		if (!*value)
		{
			free(*key);
			return (0);
		}
	}
	else
	{
		*key = ft_strdup(arg);
		if (!*key)
			return (0);
		*value = NULL;
	}
	return (1);
}

static int	process_arg(char *arg, t_env **env, int *has_error)
{
	char	*key;
	char	*value;

	if (!parse_key_value(arg, &key, &value))
		return (0);
	if (!is_valid_key(key))
	{
		print_error(key);
		*has_error = 1;
	}
	else if (!set_env(env, key, value))
	{
		free(key);
		free(value);
		return (0);
	}
	free(key);
	free(value);
	return (1);
}

int	export_builtin(char **argv, t_env **env)
{
	size_t	i;
	int		has_error;

	if (!argv[1])
	{
		print_env(*env);
		return (0);
	}
	i = 1;
	has_error = 0;
	while (argv[i])
	{
		if (!process_arg(argv[i], env, &has_error))
			return (1);
		i++;
	}
	return (has_error);
}

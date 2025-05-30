/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:35:06 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/05/30 11:26:22 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

// export 			-> print envs
// export A			-> A=NULL
// export A=		-> A=""
// export A=B		-> A=B
// export A=B C=D	-> A=B, C=D

static void print_error(char *key)
{
	ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
	ft_putstr_fd(": export: `", STDERR_FILENO);
	ft_putstr_fd(key, STDERR_FILENO);
	ft_putstr_fd("`: not a valid identifier\n", STDERR_FILENO);
}

static void print_env(t_env *env)
{
	t_env	*head;
	char	*tmp_key;
	char	*tmp_value;
	size_t	n;

	head = env;
	while (env && env->next)
	{
		if (ft_strlen(env->key) < ft_strlen(env->next->key))
			n = ft_strlen(env->key) + 1;
		else
			n = ft_strlen(env->next->key) + 1;
		if (ft_strncmp(env->key, env->next->key, n) > 0)
		{
			tmp_key = env->key;
			tmp_value = env->value;
			env->key = env->next->key;
			env->value = env->next->value;
			env->next->key = tmp_key;
			env->next->value = tmp_value;
			env = head;
			continue;
		}
		env = env->next;
	}
	env = head;
	while (env)
	{
		if (!ft_strncmp(env->key, "_", 2))
		{
			env = env->next;
			continue;
		}
		else if (env->key && env->value)
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		else if (env->key)
			printf("declare -x %s\n", env->key);
		env = env->next;
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

int	export_builtin(char **argv, t_env **env)
{
	size_t	i;
	char	*key;
	char	*value;
	int		has_error;

	if (!argv[1])
		return (print_env(*env), 0);
	i = 1;
	has_error = 0;
	while (argv[i])
	{
		if (!parse_key_value(argv[i], &key, &value))
			return (1);
		if (!is_valid_key(key))
		{
			print_error(key);
			has_error = 1;
		}
		else if (!set_env(env, key, value))
			return (free(key), free(value), 1);
		free(key);
		free(value);
		i++;
	}
	return (has_error);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:35:06 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/05/27 17:02:46 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
	while (env)
	{
		if (env->key && env->value)
			printf("%s=%s\n", env->key, env->value);
		else if (env->key)
			printf("%s=\n", env->key);
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
	int		status;

	if (!argv[1])
	{
		print_env(*env);
		return (0);
	}
	i = 1;
	while (argv[i])
	{
		if (!parse_key_value(argv[i], &key, &value))
			return (1);
		status = set_env(env, key, value);
		if (status == 0)
			return (1);
		else if (status == -1)
			print_error(key);
		free(key);
		free(value);
		i++;
	}
	return (0);
}

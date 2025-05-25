/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 11:59:23 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/05/25 17:32:42 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>

static size_t	env_list_size(t_env *env)
{
	size_t	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

static int	is_accessible(char *cmd)
{
	struct stat	sb;

	if (stat(cmd, &sb) == 0 && S_ISDIR(sb.st_mode))
	{
		ft_putstr_fd(str_arr_join((char *[]){
			SHELL_NAME, ": ", cmd, ": Is a directory\n", NULL
		}, ""), STDERR_FILENO);
		*exit_status() = WEXITSTATUS(EX_NOEXEC);
		exit(EX_NOEXEC);
	}
	else if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == -1)
			return (exit_with_error(EX_NOTFOUND, SHELL_NAME, 1), 0);
		if (access(cmd, X_OK) == -1)
			return (exit_with_error(EX_NOEXEC, SHELL_NAME, 1), 0);
		return (1);
	}
}

/**
 * @brief Returns full path of command if found in PATH or executable as-is.
 *
 * Checks if the command is executable directly. Otherwise, searches each PATH
 * directory for an executable file matching the command.
 *
 * @param cmd Command to locate.
 * @param env Environment list to get PATH from.
 * @return Allocated string with full path, or NULL if not found.
 */
char	*get_cmd_path(char *cmd, t_env *env)
{
	char	**env_paths;
	char	*env_path;
	char	*full_path;
	size_t	i;

	if (!cmd || !*cmd)
		return (NULL);
	if (is_accessible(cmd))
		return (ft_strdup(cmd));
	env_path = get_env_value(env, "PATH");
	if (!env_path || !*env_path)
		return (NULL);
	env_paths = ft_split(env_path, ':');
	if (!env_paths)
		return (NULL);
	i = 0;
	while (env_paths[i])
	{
		full_path = str_arr_join((char *[]){env_paths[i], cmd, NULL}, "/");
		if (full_path && !access(full_path, X_OK))
			return (free_str_arr(env_paths), full_path);
		free(full_path);
		i++;
	}
	return (free_str_arr(env_paths), NULL);
}

/**
 * @brief Converts a linked list of environment variables to a NULL-terminated
 *        array of strings in "KEY=VALUE" format.
 *
 * Allocates memory for the array and strings. Caller is responsible for freeing
 * the returned array and its contents.
 *
 * @param env Pointer to the head of the t_env linked list.
 * @return char** Array of strings representing the environment variables.
 * NULL if allocation fails.
 */
char	**env2envp(t_env *env)
{
	char	**envp;
	t_env	*tmp;
	size_t	size;

	size = env_list_size(env);
	if (size == 0)
		return (NULL);
	envp = malloc(sizeof(char *) * (size + 1));
	if (!envp)
		return (NULL);
	tmp = env;
	while (tmp)
	{
		*envp = str_arr_join((char *[]){tmp->key, tmp->value, NULL}, "=");
		if (!*envp)
			return (free_str_arr(envp), NULL);
		tmp = tmp->next;
		envp++;
	}
	*envp = NULL;
	return (envp - size);
}

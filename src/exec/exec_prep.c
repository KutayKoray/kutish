/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 11:59:23 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/06/12 18:56:06 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

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

static int	is_accessible(t_cmd *cmd)
{
	struct stat	sb;

	if (ft_strchr(cmd->argv[0], '/'))
	{
		if (stat(cmd->argv[0], &sb) == 0 && S_ISDIR(sb.st_mode))
		{
			ft_putstr_fd(SHELL_NAME, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(cmd->argv[0], 2);
			ft_putstr_fd(": Is a directory\n", 2);
			free_lists();
			exit_with_error(EX_NOEXEC, NULL, 1);
		}
		if (access(cmd->argv[0], F_OK) == -1)
			return (free_lists(),
				exit_with_error(EX_NOTFOUND, SHELL_NAME, 1), 0);
		if (access(cmd->argv[0], X_OK) == -1)
			return (free_lists(),
				exit_with_error(EX_NOEXEC, SHELL_NAME, 1), 0);
		return (1);
	}
	return (0);
}

char	*get_cmd_path(t_cmd *cmd, t_env *env)
{
	char	**paths;
	char	*path;
	char	*full_path;
	size_t	i;

	if (!cmd->argv[0] || !*cmd->argv[0])
		return (NULL);
	if (is_accessible(cmd))
		return (ft_strdup(cmd->argv[0]));
	path = get_env_value(env, "PATH");
	if (!path || !*path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = str_arr_join((char *[]){paths[i], cmd->argv[0], NULL}, "/");
		if (full_path && !access(full_path, X_OK))
			return (free_str_arr(paths), full_path);
		free(full_path);
		i++;
	}
	return (free_str_arr(paths), NULL);
}

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

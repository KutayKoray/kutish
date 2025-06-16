/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 11:59:23 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/06/16 20:32:03 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

static void	print_is_a_dir_error(char *cmd)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": Is a directory\n", 2);
	free_lists();
	exit_with_error(EX_NOEXEC, NULL, 1);
}

static int	is_accessible(t_cmd *cmd)
{
	struct stat	sb;

	if (ft_strchr(cmd->argv[0], '/'))
	{
		if (stat(cmd->argv[0], &sb) == 0 && S_ISDIR(sb.st_mode))
			print_is_a_dir_error(cmd->argv[0]);
		if (access(cmd->argv[0], F_OK) == -1)
		{
			free_lists();
			exit_with_error(EX_NOTFOUND, SHELL_NAME, 1);
		}
		if (access(cmd->argv[0], X_OK) == -1)
		{
			free_lists();
			exit_with_error(EX_NOEXEC, SHELL_NAME, 1);
		}
		return (1);
	}
	return (0);
}

static char	*search_path_dirs(char **paths, char *cmd_name)
{
	char	*full_path;
	size_t	i;

	i = 0;
	while (paths[i])
	{
		full_path = str_arr_join((char *[]){paths[i], cmd_name, NULL}, "/");
		if (full_path && !access(full_path, X_OK))
		{
			free_str_arr(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_str_arr(paths);
	return (NULL);
}

char	*get_cmd_path(t_cmd *cmd, t_env *env)
{
	char	**paths;
	char	*path;

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
	return (search_path_dirs(paths, cmd->argv[0]));
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
		{
			free_str_arr(envp);
			return (NULL);
		}
		tmp = tmp->next;
		envp++;
	}
	*envp = NULL;
	return (envp - size);
}

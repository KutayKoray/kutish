/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:37:42 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/06/14 12:07:25 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static void	print_env_error(char *var)
{
	ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
	ft_putstr_fd(": cd: ", STDERR_FILENO);
	ft_putstr_fd(var, STDERR_FILENO);
	ft_putstr_fd(": not set\n", STDERR_FILENO);
}

static void	update_env_vars(t_env **env)
{
	char	*oldpwd;
	char	*pwd;

	oldpwd = get_env_value(*env, "PWD");
	if (oldpwd)
		set_env(env, "OLDPWD", oldpwd);
	pwd = getcwd(NULL, 0);
	if (pwd)
		set_env(env, "PWD", pwd);
	free(pwd);
}

int	cd_builtin(char **argv, t_env **env)
{
	char	*path;

	if (!argv[1])
	{
		path = get_env_value(*env, "HOME");
		if (!path)
			return (print_env_error("HOME"), 1);
	}
	else if (!ft_strncmp(argv[1], "-", 2))
	{
		path = get_env_value(*env, "OLDPWD");
		if (!path)
			return (print_env_error("OLDPWD"), 1);
	}
	else if (argv[2])
	{
		ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
		ft_putstr_fd(": cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	else
		path = argv[1];
	if (chdir(path) == -1)
		return (perror(path), 1);
	return (update_env_vars(env), 0);
}

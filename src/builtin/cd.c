/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:37:42 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/06/16 19:18:09 by ebabaogl         ###   ########.fr       */
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

static void	print_too_many_args_error(void)
{
	ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
	ft_putstr_fd(": cd: too many arguments\n", STDERR_FILENO);
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
		{
			print_env_error("HOME");
			return (1);
		}
	}
	else if (argv[2])
	{
		print_too_many_args_error();
		return (1);
	}
	else
		path = argv[1];
	if (chdir(path) == -1)
	{
		exit_with_error(EXECUTION_FAILURE, SHELL_NAME, 0);
		return (1);
	}
	update_env_vars(env);
	return (0);
}

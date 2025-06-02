/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 20:21:53 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/06/02 19:26:00 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_shlvl(t_env **env)
{
	char	*shlvl_env;
	char	*new_shlvl;

	shlvl_env = get_env_value(*env, "SHLVL");
	if (!shlvl_env)
	{
		if (!set_env(env, "SHLVL", "1"))
			return (0);
	}
	else
	{
		new_shlvl = ft_itoa(ft_atoi(shlvl_env) + 1);
		if (!new_shlvl)
			return (0);
		if (!set_env(env, "SHLVL", new_shlvl))
		{
			free(new_shlvl);
			return (0);
		}
		free(new_shlvl);
	}
	return (1);
}

static int	init_pwd(t_env **env)
{
	char	*pwd;

	if (!get_env_value(*env, "PWD"))
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
			return (0);
		if (!set_env(env, "PWD", pwd))
		{
			free(pwd);
			return (0);
		}
		free(pwd);
	}
	return (1);
}

static int	init_oldpwd(t_env **env)
{
	if (!get_env_value(*env, "OLDPWD"))
	{
		if (!set_env(env, "OLDPWD", NULL))
			return (0);
	}
	return (1);
}

void	initialize_envs(t_env **env)
{
	if (!init_oldpwd(env))
		return ;
	if (!init_pwd(env))
		return ;
	if (!init_shlvl(env))
		return ;
}

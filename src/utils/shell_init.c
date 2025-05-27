/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:07:15 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/05/27 19:07:28 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"

void	initialize_envs(t_env **env)
{
	char	*shlvl_env;
	char	*new_shlvl;

	shlvl_env = get_env_value(*env, "SHLVL");
	if (!shlvl_env)
		append_env_node(env, "SHLVL", "1");
	else
	{
		new_shlvl = ft_itoa(ft_atoi(shlvl_env) + 1);
		if (!new_shlvl)
			return ;
		set_env(env, "SHLVL", new_shlvl);
	}
}
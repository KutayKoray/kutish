/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:20:31 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/05/30 14:28:41 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	print_env_reverse(t_env *env)
{
	if (!env)
		return;
	print_env_reverse(env->next);
	if (env->value)
	{
		ft_putstr_fd(env->key, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putstr_fd(env->value, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
}

int	env_builtin(t_env *env)
{
	print_env_reverse(env);
	return (0);
}

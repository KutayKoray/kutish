/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:04:41 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/05/23 02:35:03 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdlib.h>

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argc;
	(void)argv;
	env = init_env_list(envp);
	if (!env)
		return (EXIT_FAILURE);
	return (0);
}

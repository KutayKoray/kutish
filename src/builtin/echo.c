/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:53:32 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/05/27 16:23:18 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "exec.h"
#include "libft.h"
#include <unistd.h>

static int	handle_flags(char *arg, int *nl_flag)
{
	static int	false_flag = 0;
	size_t	j;

	if (arg[0] != '-' || false_flag)
		return (0);
	j = 0;
	while (arg[++j])
	{
		while (arg[j] == 'n')
			j++;
		if (!arg[j])
			return (*nl_flag = 0, 1);
		else
		{
			false_flag = 1;
			break ;
		}
	}
	return (0);
}

int	echo_builtin(char **argv)
{
	size_t	i;
	int		nl_flag;
	int		skip_flag;

	i = 1;
	nl_flag = 1;
	while (argv[i])
	{
		skip_flag = handle_flags(argv[i], &nl_flag);
		if (skip_flag)
		{
			i++;
			continue;
		}
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (argv[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (nl_flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}

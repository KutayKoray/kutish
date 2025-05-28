/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:53:32 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/05/28 14:44:12 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/**
 * @brief Outputs the arguments to standard output, handling the -n flag.
 * If the -n flag is present, it does not output a newline at the end.
 * 
 * @example
 * * echo 42        -> 42
 * * echo -n 42     -> 42 (without newline)
 * * echo -n -n 42  -> 42 (without newline)
 * * echo -n -z 42  -> -z 42 (without newline) (-z is not a valid flag)
 * * echo -z -n 42  -> -z -n 42 (-z is not a valid flag)
 * * echo -nnnn 42 -> 42 (without newline)
 * 
 * @param argv The array of arguments passed to the echo command.
 * @return int Returns 0 on success.
 */
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

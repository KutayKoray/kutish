/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoray <kkoray@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:21:05 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/06/01 15:22:26 by kkoray           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	print_error_sytnax(char *cmd)
{
	ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
	ft_putstr_fd(": exit: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	free_lists();
	exit_with_error(2, NULL, 1);
}

static void	print_error_many_arg(void)
{
	ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
	ft_putstr_fd(": exit: too many arguments\n", STDERR_FILENO);
	exit_with_error(1, NULL, 0);
}

static int	ft_isnum(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i] || str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
				i++;
			if (str[i])
				return (0);
			return (1);
		}
		i++;
	}
	return (1);
}

static int	ft_atol(const char *str, long *out)
{
	int		sign;
	long	result;
	size_t	i;

	sign = 1;
	result = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	while (ft_isdigit(str[i]))
	{
		if (result > (LONG_MAX - (str[i] - '0')) / 10)
			return (-1);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i])
		return (-1);
	*out = result * sign;
	return (0);
}

// X -> noexit   code 1   bash: exit: too many arguments
// Y -> exit     code 2   bash: exit: a: numeric argument required

// exit       -> exit with last exit code
// exit 11    -> exit with code 11
// exit 11 a  -> X
// exit 11 11 -> X!ft_isnum(cmd->argv[1])
// exit a     -> Y
// exit a 11  -> Y
// exit a a   -> Y
// exit +-11  -> Y
// exit long+ -> Y
int	exit_builtin(t_cmd *cmd)
{
	long	exit_code;
	int		status;

	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (!cmd->argv[1])
	{
		free_lists();
		exit_with_error(*exit_status(), NULL, 1);
	}
	status = ft_atol(cmd->argv[1], &exit_code);
	if (!ft_isnum(cmd->argv[1]) || status == -1)
		print_error_sytnax(cmd->argv[1]);
	if (cmd->argv[2] || status == -1)
		return (print_error_many_arg(), 1);
	if (cmd->argv[1])
	{
		free_lists();
		exit_with_error(exit_code % 256, NULL, 1);
	}
	return (1);
}

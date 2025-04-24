/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoray <kkoray@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:18:35 by kkoray            #+#    #+#             */
/*   Updated: 2024/11/14 15:45:47 by kkoray           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

ssize_t	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

static ssize_t	ft_putstr(char *str)
{
	ssize_t	i;
	ssize_t	check_error;

	i = 0;
	while (str[i])
	{
		check_error = write(1, &str[i], 1);
		if (check_error == -1)
			return (check_error);
		i++;
	}
	return (i);
}

ssize_t	print_str(char *s)
{
	ssize_t	i;
	int		check_error;

	i = 0;
	check_error = 0;
	if (s == NULL)
		return (ft_putstr("(null)"));
	while (s[i])
	{
		check_error = ft_putchar(s[i]);
		if (check_error == -1)
			return (-1);
		i++;
	}
	return (i);
}

ssize_t	print_str_free(char *s)
{
	ssize_t	i;
	int		check_error;

	i = 0;
	check_error = 0;
	if (s == NULL)
	{
		return (ft_putstr("(null)"));
	}
	while (s[i])
	{
		check_error = ft_putchar(s[i]);
		if (check_error == -1)
			return (-1);
		i++;
	}
	free(s);
	return (i);
}

char	*to_upper(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 32;
		i++;
	}
	return (str);
}

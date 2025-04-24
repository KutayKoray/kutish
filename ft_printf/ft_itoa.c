/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoray <kkoray@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 15:33:12 by kkoray            #+#    #+#             */
/*   Updated: 2024/11/13 17:39:57 by kkoray           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

void	reverse(char *buffer, unsigned long length)
{
	int		start;
	int		end;
	char	temp;

	start = 0;
	end = length - 1;
	while (start < end)
	{
		temp = buffer[start];
		buffer[start] = buffer[end];
		buffer[end] = temp;
		start++;
		end--;
	}
}

static int	handle_negative(int *value)
{
	if (*value < 0)
	{
		*value = -*value;
		return (1);
	}
	return (0);
}

static char	*ft_strcpy(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = s2[i];
	return (s1);
}

static int	get_length(int value, int base)
{
	int	length;

	length = 0;
	if (value == 0)
		return (1);
	while (value != 0)
	{
		length++;
		value = value / base;
	}
	return (length);
}

char	*ft_itoa(int value, int base)
{
	int		i;
	int		is_negative;
	char	*buffer;

	i = 0;
	if (value == -2147483648)
		return (buffer = malloc(12 * sizeof(char)), ft_strcpy(buffer,
				"-2147483648"), buffer);
	is_negative = handle_negative(&value);
	buffer = malloc((get_length(value, base) + 1 + is_negative) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (value == 0)
		return (buffer[i++] = '0', buffer[i] = '\0', buffer);
	while (value != 0)
	{
		if (value % base > 9)
			buffer[i++] = value % base - 10 + 'a';
		else
			buffer[i++] = value % base + '0';
		value = value / base;
	}
	if (is_negative)
		buffer[i++] = '-';
	return (buffer[i] = '\0', reverse(buffer, i), buffer);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoray <kkoray@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 15:33:16 by kkoray            #+#    #+#             */
/*   Updated: 2024/11/13 16:59:07 by kkoray           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

static unsigned long	get_length_uitoa(unsigned long value, int base)
{
	unsigned long	length;

	length = 0;
	if (value == 0)
	{
		return (1);
	}
	while (value != 0)
	{
		length++;
		value = value / base;
	}
	return (length);
}

static char	*fill_buffer(char *buffer, unsigned long value, int base,
		unsigned long *index)
{
	int				remainder;
	unsigned long	i;

	i = *index;
	if (value == 0)
	{
		buffer[i++] = '0';
		buffer[i] = '\0';
		return (buffer);
	}
	while (value != 0)
	{
		remainder = value % base;
		if (remainder > 9)
			buffer[i++] = remainder - 10 + 'a';
		else
			buffer[i++] = remainder + '0';
		value = value / base;
	}
	buffer[i] = '\0';
	*index = i;
	return (buffer);
}

char	*ft_uitoa(unsigned long value, int base)
{
	unsigned long	length;
	char			*buffer;
	unsigned long	i;

	i = 0;
	length = get_length_uitoa(value, base);
	buffer = malloc((length + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	buffer = fill_buffer(buffer, value, base, &i);
	reverse(buffer, i);
	return (buffer);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoray <kkoray@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:52:30 by kkoray            #+#    #+#             */
/*   Updated: 2024/11/14 16:14:48 by kkoray           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>
#include <unistd.h>

static ssize_t	print_char(int c)
{
	return (ft_putchar(c));
}

static ssize_t	print_ptr(void *val)
{
	ssize_t	len;

	len = 0;
	if (val == NULL)
		return (print_str("(nil)"));
	len += print_str("0x");
	len += print_str_free(ft_uitoa((unsigned long)val, 16));
	return (len);
}

static int	v_format(va_list va, const char format)
{
	ssize_t	len;

	if (!format)
		return (-1);
	len = 0;
	if (format == 'c')
		len += print_char(va_arg(va, int));
	else if (format == 's')
		len += print_str(va_arg(va, char *));
	else if (format == 'd' || format == 'i')
		len += print_str_free(ft_itoa(va_arg(va, int), 10));
	else if (format == 'u')
		len += print_str_free(ft_uitoa(va_arg(va, unsigned int), 10));
	else if (format == 'x')
		len += print_str_free(ft_uitoa(va_arg(va, unsigned int), 16));
	else if (format == 'X')
		len += print_str_free(to_upper(ft_uitoa(va_arg(va, unsigned int), 16)));
	else if (format == 'p')
		len += print_ptr(va_arg(va, void *));
	else if (format == '%')
		len += print_char('%');
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	va;
	int		len;
	int		is_error;

	len = 0;
	va_start(va, format);
	while (*format)
	{
		if (*format == '%')
		{
			is_error = 0;
			format++;
			is_error += v_format(va, *format);
			if (is_error == -1)
				return (-1);
			len += is_error;
		}
		else
			len += print_char(*format);
		format++;
	}
	va_end(va);
	return (len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoray <kkoray@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:53:02 by kkoray            #+#    #+#             */
/*   Updated: 2024/11/13 22:38:42 by kkoray           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>

ssize_t	ft_putchar(char c);
char	*ft_itoa(int n, int base);
ssize_t	print_str(char *s);
char	*to_upper(char *str);
char	*ft_uitoa(unsigned long value, int base);
void	reverse(char *buffer, unsigned long length);
int		ft_printf(const char *format, ...);
ssize_t	print_str_free(char *s);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoray <kkoray@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:32:34 by kkoray            #+#    #+#             */
/*   Updated: 2025/04/26 12:32:35 by kkoray           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <string.h>

/**
 * strappend_char - String'e bir karakter ekler.
 * Geriye yeni malloc'lanmış bir string döner.
 */
char	*strappend_char(char *str, char c)
{
	size_t	len;
	char	*new_str;

	if (str)
		len = strlen(str);
	else
		len = 0;
	new_str = malloc(len + 2);
	if (!new_str)
		return (NULL);
	if (str)
		ft_memcpy(new_str, str, len);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	return (new_str);
}

/**
 * strappend_str - String'e başka bir string ekler.
 * Geriye yeni malloc'lanmış bir string döner.
 */
char	*strappend_str(char *str, const char *suffix)
{
	size_t	len1;
	size_t	len2;
	char	*new_str;

	if (str)
		len1 = strlen(str);
	else
		len1 = 0;
	if (suffix)
		len2 = strlen(suffix);
	else
		len2 = 0;
	new_str = malloc(len1 + len2 + 1);
	if (!new_str)
		return (NULL);
	if (str)
		ft_memcpy(new_str, str, len1);
	if (suffix)
		ft_memcpy(new_str + len1, suffix, len2);
	new_str[len1 + len2] = '\0';
	return (new_str);
}

/**
 * get_num_length - Sayının uzunluğunu hesaplayan recursive fonksiyon.
 */
int	get_num_length(unsigned int num)
{
	if (num == 0)
		return (0);
	return (1 + get_num_length(num / 10));
}

/*
n'e kadar kopyası olan yeni bir dize ayırır ve döndürür
girişten karakterler.
*/
char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	i;

	dup = (char *)malloc(sizeof(char) * (n + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < n && s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

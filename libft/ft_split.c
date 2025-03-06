/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoray <kkoray@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:03:03 by kkoray            #+#    #+#             */
/*   Updated: 2024/10/19 20:53:02 by kkoray           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	count_words(const char *str, char c);
static void	*free_all(char **s);
static char	*parse_word(const char *str, char sep);

char	**ft_split(char const *s, char c)
{
	char	**split;
	char	**start;

	if (!s)
		return (NULL);
	split = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	start = split;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			*split = parse_word(s, c);
			if (!*split)
				return (free_all(start));
			split++;
		}
		while (*s && *s != c)
			s++;
	}
	*split = NULL;
	return (start);
}

static char	*parse_word(const char *str, char sep)
{
	int		len;
	char	*s;

	len = 0;
	while (str[len] && str[len] != sep)
		len++;
	s = (char *)malloc((len + 1) * sizeof(char));
	if (!s)
		return (NULL);
	ft_memcpy(s, str, len);
	s[len] = '\0';
	return (s);
}

static void	*free_all(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

static int	count_words(const char *str, char sep)
{
	int	i;
	int	count;
	int	in_word;

	i = 0;
	count = 0;
	in_word = 0;
	while (str[i])
	{
		if (str[i] != sep && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (str[i] == sep)
		{
			in_word = 0;
		}
		i++;
	}
	return (count);
}

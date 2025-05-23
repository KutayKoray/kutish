/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:50:19 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/05/23 16:04:33 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/**
 * @brief Joins an array of strings with a separator into a single string.
 *
 * Allocates and returns a new string consisting of all elements in the given
 * NULL-terminated string array, joined by the specified separator string.
 *
 * @param arr A NULL-terminated array of strings to join.
 * @param sep The separator string to insert between elements.
 * @return char* A newly allocated joined string, or NULL on failure.
 */
char	*str_arr_join(char **arr, char *sep)
{
	char	*res;
	size_t	len;
	size_t	i;

	if (!arr || !*arr || !sep)
		return (NULL);
	len = 0;
	i = 0;
	while (arr[i])
		len += ft_strlen(arr[i++]) + ft_strlen(sep);
	if (i > 0)
		len -= ft_strlen(sep);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	*res = '\0';
	i = 0;
	while (arr[i])
	{
		ft_strlcat(res, arr[i], len + 1);
		if (arr[i + 1])
			ft_strlcat(res, sep, len + 1);
		i++;
	}
	return (res);
}

/**
 * @brief Frees a NULL-terminated array of strings.
 *
 * Iterates through the given array of strings, freeing each string,
 * and finally frees the array pointer itself. If the array is NULL,
 * the function does nothing.
 *
 * @param arr A NULL-terminated array of dynamically allocated strings.
 */
void	free_str_arr(char **arr)
{
	size_t	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

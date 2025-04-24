/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoray <kkoray@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:56:29 by kkoray            #+#    #+#             */
/*   Updated: 2024/10/23 16:59:25 by kkoray           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*tmp_dst;
	unsigned char	*tmp_src;

	if (!dst && !src)
		return (NULL);
	tmp_dst = (unsigned char *)dst;
	tmp_src = (unsigned char *)src;
	if (tmp_dst > tmp_src && tmp_dst < tmp_src + len)
	{
		while (len > 0)
		{
			*(tmp_dst + len - 1) = *(tmp_src + len - 1);
			len--;
		}
	}
	else
	{
		while (len > 0)
		{
			*(tmp_dst++) = *(tmp_src++);
			len--;
		}
	}
	return (dst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoray <kkoray@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:07:43 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/05/29 20:08:41 by kkoray           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

// str_utils.c
char	*str_arr_join(char **arr, char *sep);
void	free_str_arr(char **arr);
int     ft_strcmp(const char *s1, const char *s2);
char	*ft_strndup(const char *s, size_t n);

#endif
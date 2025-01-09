/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:39:19 by gtoure            #+#    #+#             */
/*   Updated: 2024/11/04 20:46:20 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat_lib(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	len_dst;

	if ((src == NULL || dst == NULL) && size == 0)
		return (0);
	i = 0;
	j = 0;
	len_dst = ft_strlen_lib(dst);
	if (size == 0)
		return (ft_strlen_lib(src));
	while (dst[i] != '\0' && i < size)
		i++;
	while (src[j] != '\0' && i < size - 1)
		dst[i++] = src[j++];
	if (size != 0 && size >= len_dst)
		dst[i] = '\0';
	if (size < ft_strlen_lib(dst))
		return (ft_strlen_lib(src) + size);
	return (ft_strlen_lib(src) + len_dst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:42:17 by gtoure            #+#    #+#             */
/*   Updated: 2024/11/04 20:48:03 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr_lib(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;
	size_t	n_len;
	char	*str;

	if (haystack == NULL || needle == NULL)
		return (0);
	i = 0;
	j = 0;
	n_len = ft_strlen_lib(needle);
	str = (char *)haystack;
	if (needle == haystack || n_len == 0)
		return (str);
	while (str[i])
	{
		j = 0;
		while (str[i + j] != '\0' && needle[j] != '\0' && str[i + j]
			== needle[j])
			j++;
		if (j == n_len)
			return (ft_strdup_lib(str + i));
		i++;
	}
	return (NULL);
}

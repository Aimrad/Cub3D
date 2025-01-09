/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:44:30 by gtoure            #+#    #+#             */
/*   Updated: 2024/11/04 20:50:56 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

char	*ft_substr_lib(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	s_len;

	i = 0;
	s_len = ft_strlen_lib(s);
	if (start > s_len)
	{
		sub = malloc(sizeof(char));
		if (!sub)
			return (NULL);
		sub[0] = '\0';
		return (sub);
	}
	if (start + len > s_len)
		len = (unsigned long int) s_len - start;
	sub = malloc(sizeof(char) * len + 1);
	if (!sub)
		return (NULL);
	while (s[start] && i < len)
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}

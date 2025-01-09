/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:34:50 by gtoure            #+#    #+#             */
/*   Updated: 2024/05/14 15:23:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	size_of_line(char *line, int status, char **env)
{
	int		i;
	size_t	size;

	i = 0;
	size = 0;
	while (line[i])
	{
		if ((line[i] == '$' && (ft_isalnum_lib(line[i + 1])
					|| line[i + 1] == '_')) || line[i + 1] == '?')
			size += expansion(line, &i, status, env);
		else
			size += regular(line, &i, status, env);
	}
	return (size);
}

size_t	ft_gnlstrlen(char *str)
{
	size_t	c;

	c = 0;
	if (!str)
		return (0);
	while (str[c] != '\0')
		c++;
	return (c);
}

char	*ft_gnlstrchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_gnlstrlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*ft_gnlstrjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	c;
	char	*str;

	if (!s1)
		s1 = ft_gnlstrdup("");
	if (!s1 || !s2)
		return (NULL);
	str = malloc((ft_gnlstrlen(s1) + ft_gnlstrlen(s2) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = -1;
	c = 0;
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	while (s2[c] != '\0')
		str[i++] = s2[c++];
	str[ft_gnlstrlen(s1) + ft_gnlstrlen(s2)] = '\0';
	free(s1);
	return (str);
}

char	*ft_gnlstrdup(char *s)
{
	char	*sd;
	size_t	i;

	i = 0;
	sd = malloc(sizeof(char) * ft_gnlstrlen(s) + 1);
	if (!sd)
		return (NULL);
	while (s[i] != '\0')
	{
		sd[i] = s[i];
		i++;
	}
	sd[i] = '\0';
	return (sd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 23:43:13 by marvin            #+#    #+#             */
/*   Updated: 2024/11/20 17:17:39 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_save(char *save)
{
	int		i;
	int		c;
	char	*s;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	s = (char *)malloc(sizeof(char) * (ft_gnlstrlen(save) - i + 1));
	if (!s)
		return (NULL);
	i++;
	c = 0;
	while (save[i])
		s[c++] = save[i++];
	s[c] = '\0';
	free(save);
	return (s);
}

char	*ft_get_line(char *save)
{
	int		i;
	char	*s;

	i = 0;
	if (!save[i])
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	s = (char *)malloc(sizeof(char) * (i + 2));
	if (!s)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		s[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		s[i] = save[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_save_and_read(int fd, char *save)
{
	int		byte;
	char	*buff;

	byte = 1;
	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	while (!ft_gnlstrchr(save, '\n') && byte != 0)
	{
		byte = read(fd, buff, BUFFER_SIZE);
		if (byte == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[byte] = '\0';
		save = ft_gnlstrjoin(save, buff);
	}
	free(buff);
	return (save);
}

char	*expand(char *line, int status, char **env)
{
	t_expand_gnl	ctx;

	ctx.i = 0;
	ctx.j = 0;
	ctx.k = 0;
	ctx.size = size_of_line(line, status, env);
	ctx.result = malloc((ctx.size + 2) * sizeof(char));
	if (!ctx.result)
		return (NULL);
	while (line[ctx.i] && line[ctx.i] != '\n')
	{
		if (line[ctx.i] == '$' && (ft_isalnum_lib(line[ctx.i + 1])
				|| line[ctx.i + 1] == '_' || line[ctx.i + 1] == '?'))
			copy_expand(&ctx, line, status, env);
		else
			copy_char(&ctx, line);
	}
	if (line[ctx.i] == '\n')
		ctx.result[ctx.k++] = line[ctx.i++];
	ctx.result[ctx.k] = '\0';
	free(line);
	return (ctx.result);
}

char	*get_next_line(int fd, int flag, int status, char **env)
{
	char		*line;
	static char	*save;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (flag == 1)
	{
		free(save);
		return (NULL);
	}
	save = ft_save_and_read(fd, save);
	if (!save)
		return (NULL);
	line = ft_get_line(save);
	save = ft_save(save);
	if (flag == 2)
		line = expand(line, status, env);
	if (line && line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}

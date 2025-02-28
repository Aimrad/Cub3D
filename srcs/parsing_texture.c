/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artheon <artheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:37:46 by artheon           #+#    #+#             */
/*   Updated: 2025/02/28 17:33:13 by artheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	count_texture(char *line, int *i)
{
	int	nb_tex;
	int	j;

	nb_tex = 1;
	j = *i;
	while (line[j])
	{
		if (line[j] == ',')
			nb_tex++;
		j++;
	}
	return (nb_tex);
}

int	alloc_texture_char(char ***texture, int nb_tex)
{
	*texture = malloc(sizeof(char *) * (nb_tex + 1));
	if (!*texture)
		return (error_exit("Error\nMalloc failed\n", 0), 1);
	(*texture)[nb_tex] = NULL;
	return (0);
}

char	**split_texture(char *line, int *i)
{
	char	**texture_tab;

	while (line[*i] && (line[*i] == ' ' || line[*i] == '\t'))
		(*i)++;
	texture_tab = ft_split(line + *i, ',');
	if (!texture_tab)
		error_exit("Error\nMalloc failed\n", 0);
	return (texture_tab);
}

static int	free_path(char ***texture, char **tex_tab, int j, char *msg)
{
	while (j > 0)
	{
		free((*texture)[j]);
		j--;
	}
	free(*texture);
	free_split(tex_tab);
	return (error_exit(msg, 0), 1);
}

int	parse_texture(char ***texture, char **texture_tab, int nb_tex)
{
	int	fd;
	int	j;

	j = 0;
	while (j < nb_tex)
	{
		trim_whitespace(texture_tab[j]);
		fd = open(texture_tab[j], O_RDONLY);
		if (fd < 0)
			return (free_path(texture, texture_tab, j, \
				"Error\nTexture introuvable\n"));
		close(fd);
		(*texture)[j] = ft_strdup(texture_tab[j]);
		if (!(*texture)[j])
			return (free_path(texture, texture_tab, j, \
				"Error\nMalloc failed\n"));
		j++;
	}
	return (0);
}

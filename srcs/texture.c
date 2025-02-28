/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artheon <artheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:42:38 by artheon           #+#    #+#             */
/*   Updated: 2025/02/28 15:32:57 by artheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	load_single_texture(t_game *game, t_texture *tex, char *path, int i)
{
	int		bit_per_pixel;
	int		line_length;
	int		endian;

	tex->img[i] = mlx_xpm_file_to_image(game->mlx, path, &tex->width, \
		&tex->height);
	if (!tex->img[i])
	{
		printf("Erreur lors du chargement de la texture %s\n", path);
		exit(EXIT_FAILURE);
	}
	tex->data[i] = (int *)mlx_get_data_addr(tex->img[i], &bit_per_pixel, \
		&line_length, &endian);
}

void	load_texture(t_game *game, t_texture *tex, char **path)
{
	int		i;

	tex->frame_count = 0;
	while (path[tex->frame_count])
		tex->frame_count++;
	tex->img = malloc(sizeof(void *) * tex->frame_count);
	tex->data = malloc(sizeof(int *) * tex->frame_count);
	if (!tex->img || !tex->data)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < tex->frame_count)
	{
		load_single_texture(game, tex, path[i], i);
		i++;
	}
}

void	load_all_texture(t_game *game)
{
	load_texture(game, &game->texture[0], game->config.texture_no);
	load_texture(game, &game->texture[1], game->config.texture_so);
	load_texture(game, &game->texture[2], game->config.texture_we);
	load_texture(game, &game->texture[3], game->config.texture_ea);
}

int	get_texture_index(int side, double ray_dir_x, double ray_dir_y)
{
	if (side == 0)
	{
		if (ray_dir_x > 0)
			return (3);
		else
			return (2);
	}
	else
	{
		if (ray_dir_y > 0)
			return (1);
		else
			return (0);
	}
}

int	parse_color(char *line, int *i)
{
	int		j;
	char	*rgb;
	int		value;

	j = 0;
	while (line[*i] && line[*i] != ',')
	{
		if (line[*i] < '0' || line[*i] > '9')
			return (error_exit("Error\nColor args: invalide form\n", 0), -1);
		j++;
		(*i)++;
	}
	rgb = ft_substr(line, *i - j, j);
	value = (int)ft_atoi(rgb);
	free(rgb);
	if (value < 0 || value > 255)
		return (error_exit("Error\nColor args: 0-255\n", 0), free(rgb), -1);
	return (value);
}

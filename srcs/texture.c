/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artheon <artheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:42:38 by artheon           #+#    #+#             */
/*   Updated: 2025/02/19 15:22:42 by artheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	load_texture(t_game *game, t_texture *tex, char *path)
{
	int		bit_per_pixel;
	int		line_length;
	int		endian;

	tex->img = mlx_xpm_file_to_image(game->mlx, path, &tex->width, \
		&tex->height);
	if (!tex->img)
	{
		printf("Erreur lors du chargement de la texture %s\n", path);
		exit(EXIT_FAILURE);
	}
	tex->data = (int *)mlx_get_data_addr(tex->img, &bit_per_pixel, \
		&line_length, &endian);
}

void	load_all_texture(t_game *game)
{
	load_texture(game, &game->texture[0], game->config->texture_no);
	load_texture(game, &game->texture[1], game->config->texture_so);
	load_texture(game, &game->texture[2], game->config->texture_we);
	load_texture(game, &game->texture[3], game->config->texture_ea);
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

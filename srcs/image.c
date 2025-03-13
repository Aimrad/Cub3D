/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artheon <artheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:43:45 by artheon           #+#    #+#             */
/*   Updated: 2025/03/13 18:41:35 by artheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_image(t_game *game)
{
	int	size;

	size = MINIMAP_RADIUS * 2;
	game->img.img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp, \
		&game->img.size_line, &game->img.endian);
	game->mini_map.img = mlx_new_image(game->mlx, size, size);
	game->mini_map.addr = mlx_get_data_addr(game->mini_map.img, \
		&game->mini_map.bpp, &game->mini_map.size_line, &game->mini_map.endian);
}

static int	is_whithin_minimap_radius(int x, int y, int center)
{
	int	dx;
	int	dy;

	dx = x - center;
	dy = y - center;
	return (dx * dx + dy * dy <= MINIMAP_RADIUS * MINIMAP_RADIUS);
}

void	put_pixel_mini_map(t_game *game, int x, int y, int color)
{
	int	pixel;
	int	pixel_size;
	int	i;
	int	j;
	int	center;

	center = MINIMAP_RADIUS;
	pixel_size = 5;
	if (!is_whithin_minimap_radius(x, y, center))
		return ;
	i = 0;
	while (i < pixel_size)
	{
		j = 0;
		while (j < pixel_size)
		{
			pixel = ((y + j) * game->mini_map.size_line + (x + i) * \
			(game->mini_map.bpp / 8));
			*(unsigned int *)(game->mini_map.addr + pixel) = color;
			j++;
		}
		i++;
	}
}

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	int	pixel;

	pixel = (y * game->img.size_line + x * (game->img.bpp / 8));
	*(unsigned int *)(game->img.addr + pixel) = color;
}

void	clear_image(t_game *game)
{
	int	*pixels;
	int	i;

	i = 0;
	pixels = (int *)game->img.addr;
	while (i < SCREEN_WIDTH * SCREEN_HEIGHT)
	{
		pixels[i] = 0;
		i++;
	}
}

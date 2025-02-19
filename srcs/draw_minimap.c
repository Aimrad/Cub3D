/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artheon <artheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:21:16 by artheon           #+#    #+#             */
/*   Updated: 2025/02/19 18:21:26 by artheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	draw_minimap_tile(t_game *game, int y, int x, int mini_tile)
{
	int	color;
	int	i;
	int	j;

	if (game->grid[y][x] == '1')
		color = 0xFFFFFF;
	else
		color = 0x000000;
	i = 0;
	while (i < mini_tile)
	{
		j = 0;
		while (j < mini_tile)
		{
			put_pixel_mini_map(game, x * mini_tile + i, \
				y * mini_tile + j, color);
			j++;
		}
		i++;
	}
}

static void	draw_player_and_dir(t_game *game, int px, int py)
{
	int	i;
	int	j;

	i = -5;
	while (i <= 5)
	{
		j = -5;
		while (j <= 5)
		{
			put_pixel_mini_map(game, px + i, py + j, 0xFF0000);
			j++;
		}
		i++;
	}
	i = 0;
	while (i < 20)
	{
		put_pixel_mini_map(game, px + (int)(game->dir_x * i), \
			py + (int)(game->dir_y * i), 0xFF0000);
		i++;
	}
}

void	draw_minimap(t_game *game)
{
	int	y;
	int	x;
	int	mini_tile;
	int	px;
	int	py;

	y = 0;
	mini_tile = 20;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			draw_minimap_tile(game, y, x, mini_tile);
			x++;
		}
		y++;
	}
	px = (int)(game->pos_x * mini_tile);
	py = (int)(game->pos_y * mini_tile);
	draw_player_and_dir(game, px, py);
	mlx_put_image_to_window(game->mlx, game->win, game->mini_map.img, 0, 0);
}

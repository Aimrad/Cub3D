/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artheon <artheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:58:58 by artheon           #+#    #+#             */
/*   Updated: 2025/02/15 17:19:40 by artheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void draw_ceiling(t_render rdr, t_game *game)
{
	rdr.y = 0;
	while (rdr.y < SCREEN_HEIGHT / 2)
	{
		rdr.x = 0;
		while (rdr.x < SCREEN_WIDTH)
		{
			my_mlx_pixel_put(game, rdr.x, \
				rdr.y, rdr.ceiling_color);
			rdr.x++;
		}
		rdr.y++;
	}
}

static void draw_floor(t_render rdr, t_game *game)
{
	rdr.y = SCREEN_HEIGHT / 2;
	while (rdr.y < SCREEN_HEIGHT)
	{
		rdr.x = 0;
		while (rdr.x < SCREEN_WIDTH)
		{
			my_mlx_pixel_put(game, rdr.x, \
				rdr.y, rdr.floor_color);
			rdr.x++;
		}
		rdr.y++;
	}
}

void	draw_background(t_render rdr, t_game *game)
{
	rdr.floor_color = create_rgb(game->config->floor_color[0], \
		game->config->floor_color[1], game->config->floor_color[2]);
	rdr.ceiling_color = create_rgb(game->config->ceiling_color[0], \
		game->config->ceiling_color[1], game->config->ceiling_color[2]);
	draw_ceiling(rdr, game);
	draw_floor(rdr, game);
}

void	draw_minimap(t_game *game)
{
	int	y;
	int	x;
	int	i;
	int	j;
	int	mini_tile;
	int	color;
	int	px;
	int	py;

	y = 0;
	mini_tile = 20;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
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
			x++;
		}
		y++;
	}
	px = (int)(game->pos_x * mini_tile);
	py = (int)(game->pos_y * mini_tile);
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
	mlx_put_image_to_window(game->mlx, game->win, game->mini_map.img, 0, 0);
}
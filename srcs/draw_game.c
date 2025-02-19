/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artheon <artheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:58:58 by artheon           #+#    #+#             */
/*   Updated: 2025/02/19 18:21:34 by artheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	draw_ceiling(t_render rdr, t_game *game)
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

static void	draw_floor(t_render rdr, t_game *game)
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

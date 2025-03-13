/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artheon <artheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:21:16 by artheon           #+#    #+#             */
/*   Updated: 2025/03/13 18:42:53 by artheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	draw_wall_tile(t_game *game, t_minimap_vars *vars, int map_x, \
	int map_y)
{
	vars->wx = vars->px + map_x;
	vars->wy = vars->py + map_y;
	vars->screen_x = vars->center + map_x * vars->scale;
	vars->screen_y = vars->center + map_y * vars->scale;
	if (vars->wx >= 0 && vars->wx < game->width && vars->wy >= 0
		&& vars->wy < game->height)
	{
		if (game->grid[vars->wy][vars->wx] == '1')
			put_pixel_mini_map(game, vars->screen_x, vars->screen_y, 0xFFFFFF);
	}
}

static void	draw_minimap_wall(t_game *game)
{
	int				map_x;
	int				map_y;
	t_minimap_vars	vars;

	vars.px = (int)game->pos_x;
	vars.py = (int)game->pos_y;
	vars.center = MINIMAP_RADIUS;
	vars.scale = 10;
	map_y = -vars.center / vars.scale;
	while (map_y < vars.center / vars.scale)
	{
		map_x = -vars.center / vars.scale;
		while (map_x < vars.center / vars.scale)
		{
			draw_wall_tile(game, &vars, map_x, map_y);
			map_x++;
		}
		map_y++;
	}
}

static void	draw_player_and_dir(t_game *game)
{
	int	px;
	int	py;
	int	dx;
	int	dy;
	int	i;

	px = MINIMAP_RADIUS;
	py = MINIMAP_RADIUS;
	i = -3;
	while (i <= -3)
	{
		put_pixel_mini_map(game, px + i, py, 0xFF0000);
		put_pixel_mini_map(game, px, py + i, 0xFF0000);
		i++;
	}
	i = 0;
	while (i < 15)
	{
		dx = px + (int)(game->dir_x * i);
		dy = py + (int)(game->dir_y * i);
		put_pixel_mini_map(game, dx, dy, 0xFF0000);
		i++;
	}
}

void	draw_minimap(t_game *game)
{
	int	size;

	size = MINIMAP_RADIUS * 2;
	mlx_destroy_image(game->mlx, game->mini_map.img);
	game->mini_map.img = mlx_new_image(game->mlx, size, size);
	game->mini_map.addr = mlx_get_data_addr(game->mini_map.img, \
		&game->mini_map.bpp, &game->mini_map.size_line, &game->mini_map.endian);
	draw_minimap_wall(game);
	draw_player_and_dir(game);
	mlx_put_image_to_window(game->mlx, game->win, game->mini_map.img, \
		SCREEN_WIDTH - MINIMAP_RADIUS * 2 - 10, \
		SCREEN_HEIGHT - MINIMAP_RADIUS * 2 - 10);
}

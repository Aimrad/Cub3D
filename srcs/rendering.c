/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artheon <artheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:45:05 by artheon           #+#    #+#             */
/*   Updated: 2025/02/15 17:50:06 by artheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void init_ray_params(t_render rdr, t_game *game)
{
	rdr.camera_x = 2 * rdr.x / (double)SCREEN_WIDTH - 1;
	rdr.ray_dir_x = game->dir_x + game->plane_x * rdr.camera_x;
	rdr.ray_dir_y = game->dir_y + game->plane_y * rdr.camera_x;
	rdr.map_x = (int)game->pos_x;
	rdr.map_y = (int)game->pos_y;
	if (rdr.ray_dir_x == 0)
		rdr.delta_dist_x = 1e30;
	else
		rdr.delta_dist_x = fabs(1 / rdr.ray_dir_x);
	if (rdr.ray_dir_y == 0)
		rdr.delta_dist_y = 1e30;
	else
		rdr.delta_dist_y = fabs(1 / rdr.ray_dir_y);
}

static void	cast_ray(t_render rdr, t_game *game)
{
	rdr.x = 0;
	while (rdr.x < SCREEN_WIDTH)
	{
		if (rdr.ray_dir_x < 0)
		{
			rdr.step_x = -1;
			rdr.side_dist_x = (game->pos_x - rdr.map_x) \
			* rdr.delta_dist_x;
		}
		else
		{
			rdr.step_x = 1;
			rdr.side_dist_x = (rdr.map_x + 1.0 - game->pos_x) \
			* rdr.delta_dist_x;
		}
		if (rdr.ray_dir_y < 0)
		{
			rdr.step_y = -1;
			rdr.side_dist_y = (game->pos_y - rdr.map_y) \
			* rdr.delta_dist_y;
		}
		else
		{
			rdr.step_y = 1;
			rdr.side_dist_y = (rdr.map_y + 1.0 - game->pos_y) \
			* rdr.delta_dist_y;
		}
		while (!rdr.hit)
		{
			if (rdr.side_dist_x < rdr.side_dist_y)
			{
				rdr.side_dist_x += rdr.delta_dist_x;
				rdr.map_x += rdr.step_x;
				rdr.side = 0;
			}
			else
			{
				rdr.side_dist_y += rdr.delta_dist_y;
				rdr.map_y += rdr.step_y;
				rdr.side = 1;
			}
			if (game->grid[rdr.map_y][rdr.map_x] == '1')
				rdr.hit = 1;
		}
		if (rdr.side == 0)
			rdr.perp_wall_dist = rdr.side_dist_x \
			- rdr.delta_dist_x;
		else
			rdr.perp_wall_dist = rdr.side_dist_y \
			- rdr.delta_dist_y;
		rdr.line_height = (int)(SCREEN_HEIGHT \
			/ rdr.perp_wall_dist);
		rdr.draw_start = -rdr.line_height \
		/ 2 + SCREEN_HEIGHT / 2;
		rdr.draw_end = rdr.line_height \
		/ 2 + SCREEN_HEIGHT / 2;
		if (rdr.draw_start < 0)
			rdr.draw_start = 0;
		if (rdr.draw_end >= SCREEN_HEIGHT)
			rdr.draw_end = SCREEN_HEIGHT - 1;
		rdr.tex_index = get_texture_index(rdr.side, \
			rdr.ray_dir_x, rdr.ray_dir_y);
		rdr.tex = &game->texture[rdr.tex_index];
		if (rdr.side == 0)
		{
			rdr.wall_x = game->pos_y + rdr.perp_wall_dist \
			* rdr.ray_dir_y;
		}
		else
		{
			rdr.wall_x = game->pos_x + rdr.perp_wall_dist \
			* rdr.ray_dir_x;
		}
		rdr.wall_x -= floor(rdr.wall_x);
		rdr.tex_x = (int)(rdr.wall_x \
			* (double)rdr.tex->width);
		if ((rdr.side == 0 && rdr.ray_dir_x > 0)
			|| (rdr.side == 1 && rdr.ray_dir_y < 0))
		{
			rdr.tex_x = rdr.tex->width \
			- rdr.tex_x - 1;
		}
		rdr.step = 1.0 * rdr.tex->height \
		/ rdr.line_height;
		rdr.tex_pos = (rdr.draw_start - SCREEN_HEIGHT / 2 \
			+ rdr.line_height / 2) * rdr.step;
		rdr.y = rdr.draw_start;
		while (rdr.y < rdr.draw_end)
		{
			rdr.tex_y = (int)rdr.tex_pos \
			& (rdr.tex->height - 1);
			rdr.tex_pos += rdr.step;
			rdr.color = rdr.tex->data[rdr.tex->height \
				* rdr.tex_y + rdr.tex_x];
			my_mlx_pixel_put(game, rdr.x, rdr.y, rdr.color);
			rdr.y++;
		}
		rdr.x++;
	}
}

int	render(t_game *game)
{
	t_render	rdr;

	clear_image(game);
	draw_background(rdr, game);
	cast_ray(rdr, game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	key(game);
	draw_minimap(game);
	return (0);
}

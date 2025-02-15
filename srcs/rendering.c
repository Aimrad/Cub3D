/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artheon <artheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:45:05 by artheon           #+#    #+#             */
/*   Updated: 2025/02/15 14:45:59 by artheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	render(t_game *map)
{
	int			x;
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		side_dist_x;
	double		side_dist_y;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	double		perp_wall_dist;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			tex_index;
	t_texture	*tex;
	double		wall_x;
	int			tex_x;
	double		step;
	double		tex_pos;
	int			y;
	int			tex_y;
	int			color;
	int			floor_color;
	int			ceiling_color;

	clear_image(map);
	y = 0;
	floor_color = create_rgb(map->config->floor_color[0], map->config->floor_color[1], map->config->floor_color[2]);
	ceiling_color = create_rgb(map->config->ceiling_color[0], map->config->ceiling_color[1], map->config->ceiling_color[2]);
	while (y < SCREEN_HEIGHT / 2)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			my_mlx_pixel_put(map, x, y, ceiling_color);
			x++;
		}
		y++;
	}
	y = SCREEN_HEIGHT / 2;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			my_mlx_pixel_put(map, x, y, floor_color);
			x++;
		}
		y++;
	}
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
		ray_dir_x = map->dir_x + map->plane_x * camera_x;
		ray_dir_y = map->dir_y + map->plane_y * camera_x;
		map_x = (int)map->pos_x;
		map_y = (int)map->pos_y;
		if (ray_dir_x == 0)
			delta_dist_x = 1e30;
		else
			delta_dist_x = fabs(1 / ray_dir_x);
		if (ray_dir_y == 0)
			delta_dist_y = 1e30;
		else
			delta_dist_y = fabs(1 / ray_dir_y);
		hit = 0;
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (map->pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - map->pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (map->pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - map->pos_y) * delta_dist_y;
		}
		while (!hit)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (map->grid[map_y][map_x] == '1')
				hit = 1;
		}
		if (side == 0)
			perp_wall_dist = side_dist_x - delta_dist_x;
		else
			perp_wall_dist = side_dist_y - delta_dist_y;
		line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);
		draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
		draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		if (draw_end >= SCREEN_HEIGHT)
			draw_end = SCREEN_HEIGHT - 1;
		tex_index = get_texture_index(side, ray_dir_x, ray_dir_y);
		tex = &map->texture[tex_index];
		if (side == 0)
			wall_x = map->pos_y + perp_wall_dist * ray_dir_y;
		else
			wall_x = map->pos_x + perp_wall_dist * ray_dir_x;
		wall_x -= floor(wall_x);
		tex_x = (int)(wall_x * (double)tex->width);
		if ((side == 0 && ray_dir_x > 0) || (side == 1 && ray_dir_y < 0))
			tex_x = tex->width - tex_x - 1;
		step = 1.0 * tex->height / line_height;
		tex_pos = (draw_start - SCREEN_HEIGHT / 2 + line_height / 2) * step;
		y = draw_start;
		while (y < draw_end)
		{
			tex_y = (int)tex_pos & (tex->height - 1);
			tex_pos += step;
			color = tex->data[tex->height * tex_y + tex_x];
			my_mlx_pixel_put(map, x, y, color);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(map->mlx, map->win, map->img.img, 0, 0);
	key(map);
	draw_minimap(map);
	return (0);
}

void	draw_minimap(t_game *game)
{
	int	y;
	int	x;
	int	i;
	int	j;
	int mini_tile;
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
					put_pixel_mini_map(game, x * mini_tile + i, y * mini_tile + j, color);
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
		put_pixel_mini_map(game, px + (int)(game->dir_x * i), py + (int)(game->dir_y * i), 0xFF0000);
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->mini_map.img, 0, 0);
}
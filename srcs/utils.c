/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils->c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artheon <artheon@student->42->fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:36:29 by artheon           #+#    #+#             */
/*   Updated: 2025/02/20 17:38:23 by artheon          ###   ########->fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	print_char(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		printf("char : %s\n", split[i]);
		i++;
	}
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	error_exit(char *msg, int flags)
{
	ft_putstr_fd(msg, 2);
	if (flags)
		exit(EXIT_FAILURE);
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	calculate_texture_and_draw_wall(t_render *rdr, t_game *game)
{
	rdr->tex_index = get_texture_index(rdr->side, rdr->ray_dir_x, rdr->ray_dir_y);
	rdr->tex = &game->texture[rdr->tex_index];
	if (rdr->side == 0)
		rdr->wall_x = game->pos_y + rdr->perp_wall_dist * rdr->ray_dir_y;
	else
		rdr->wall_x = game->pos_x + rdr->perp_wall_dist * rdr->ray_dir_x;
	rdr->wall_x -= floor(rdr->wall_x);
	rdr->tex_x = (int)(rdr->wall_x * (double)rdr->tex->width);
	if ((rdr->side == 0 && rdr->ray_dir_x > 0)
		|| (rdr->side == 1 && rdr->ray_dir_y < 0))
		rdr->tex_x = rdr->tex->width - rdr->tex_x - 1;
	rdr->step = 1.0 * rdr->tex->height / rdr->line_height;
	rdr->tex_pos = (rdr->draw_start - SCREEN_HEIGHT / 2 + rdr->line_height / 2) \
	* rdr->step;
	rdr->y = rdr->draw_start;
	while (rdr->y < rdr->draw_end)
	{
		rdr->tex_y = (int)rdr->tex_pos & (rdr->tex->height - 1);
		rdr->tex_pos += rdr->step;
		rdr->color = rdr->tex->data[rdr->tex->height * rdr->tex_y + rdr->tex_x];
		my_mlx_pixel_put(game, rdr->x, rdr->y, rdr->color);
		rdr->y++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artheon <artheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:47:08 by artheon           #+#    #+#             */
/*   Updated: 2025/02/28 17:14:01 by artheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	handle_error(t_game *map, char *msg)
{
	free_split(map->grid);
	free_split(map->config.texture_no);
	free_split(map->config.texture_so);
	free_split(map->config.texture_we);
	free_split(map->config.texture_ea);
	free(map);
	error_exit(msg, 0);
	map = NULL;
}

static void	check_and_set_player(t_game *map, int y, int x)
{
	map->pos_y = (double)y;
	map->pos_x = (double)x;
	set_player_dir(map, map->grid[y][x]);
	map->grid[y][x] = '0';
}

void	init_player_and_check_walls(t_game *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x] != '1' && (y == 0 || y == map->height - 1
				|| x == 0 || x == map->width - 1))
				return ;
			if (is_player_char(map->grid[y][x]))
				check_and_set_player(map, y, x);
			x++;
		}
		y++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artheon <artheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:15:53 by artheon           #+#    #+#             */
/*   Updated: 2025/02/28 17:13:31 by artheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	set_north_dir(t_game *map)
{
	map->dir_x = 0;
	map->dir_y = -1;
	map->plane_x = 0.66;
	map->plane_y = 0;
}

void	set_south_dir(t_game *map)
{
	map->dir_x = 0;
	map->dir_y = 1;
	map->plane_x = -0.66;
	map->plane_y = 0;
}

void	set_east_dir(t_game *map)
{
	map->dir_x = 1;
	map->dir_y = 0;
	map->plane_x = 0;
	map->plane_y = 0.66;
}

void	set_west_dir(t_game *map)
{
	map->dir_x = -1;
	map->dir_y = 0;
	map->plane_x = 0;
	map->plane_y = -0.66;
}

void	set_player_dir(t_game *map, char dir)
{
	if (dir == 'N')
		set_north_dir(map);
	else if (dir == 'S')
		set_south_dir(map);
	else if (dir == 'E')
		set_east_dir(map);
	else if (dir == 'W')
		set_west_dir(map);
}

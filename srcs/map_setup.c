/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artheon <artheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:47:08 by artheon           #+#    #+#             */
/*   Updated: 2025/02/18 19:47:48 by artheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	pad_map_lines(t_game *map)
{
	int		max_width;
	int		y;
	int		len;
	int		x;
	char	*new_line;

	max_width = (int)ft_strlen(map->grid[0]);
	y = 1;
	while (map->grid[y])
	{
		len = (int)ft_strlen(map->grid[y]);
		if (len > max_width)
			max_width = len;
		y++;
	}
	map->width = max_width;
	y = 0;
	while (y < map->height)
	{
		len = ft_strlen(map->grid[y]);
		if (len < map->width)
		{
			new_line = ft_calloc(map->width + 1, sizeof(char));
			if (!new_line)
			{
				free_split(map->grid);
				free(map);
				error_exit("Allocation mémoire échoué", 0);
				map = NULL;
				return ;
			}
			ft_memset(new_line, '1', map->width);
			ft_memcpy(new_line, map->grid[y], len);
			free(map->grid[y]);
			map->grid[y] = new_line;
		}
		else
		{
			x = 0;
			while (map->grid[y][x])
			{
				if (map->grid[y][x] == ' ')
					map->grid[y][x] = '1';
				x++;
			}
		}
		y++;
	}
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
			if (map->grid[y][x] != '1' && (y == 0 || y == map->height - 1 \
				|| x == 0 || x == map->width - 1))
			{
				free_split(map->grid);
				free(map);
				error_exit("La carte doit être fermée par des murs.", 0);
				map = NULL;
				return ;
			}
			if (is_player_char(map->grid[y][x]))
			{
				map->pos_y = (double)y;
				map->pos_x = (double)x;
				if (map->grid[y][x] == 'N')
				{
					map->dir_x = 0;
					map->dir_y = -1;
					map->plane_x = 0.66;
					map->plane_y = 0;
				}
				else if (map->grid[y][x] == 'S')
				{
					map->dir_x = 0;
					map->dir_y = 1;
					map->plane_x = -0.66;
					map->plane_y = 0;
				}
				else if (map->grid[y][x] == 'E')
				{
					map->dir_x = 1;
					map->dir_y = 0;
					map->plane_x = 0;
					map->plane_y = 0.66;
				}
				else if (map->grid[y][x] == 'W')
				{
					map->dir_x = -1;
					map->dir_y = 0;
					map->plane_x = 0;
					map->plane_y = -0.66;
				}
				map->grid[y][x] = '0';
			}
			x++;
		}
		y++;
	}
}
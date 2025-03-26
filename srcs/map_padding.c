/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_padding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artheon <artheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:18:59 by artheon           #+#    #+#             */
/*   Updated: 2025/03/19 14:11:26 by artheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	replace_spaces_with_walls(t_game *map, int y)
{
	int	x;

	x = 0;
	while (map->grid[y][x])
	{
		if (map->grid[y][x] == ' ')
			map->grid[y][x] = '1';
		x++;
	}
}

static void	pad_lines(t_game *map, int len, int y)
{
	char	*new_line;

	new_line = ft_calloc(map->width + 1, sizeof(char));
	if (!new_line)
	{
		handle_error(map, "Allocation mémoire échoué.\n");
		return ;
	}
	ft_memcpy(new_line, map->grid[y], len);
	free(map->grid[y]);
	map->grid[y] = new_line;
}

static int	is_adjacent_to_space(int x, int y, t_game *map)
{
	if (x == 0 || x == (int)ft_strlen(map->grid[y]) - 1
		|| y == 0 || y == map->height - 1)
		return (1);
	if (x > 0 && (!map->grid[y][x - 1]
		|| map->grid[y][x - 1] == ' '))
		return (1);
	if (x < (int)ft_strlen(map->grid[y]) - 1 && (!map->grid[y][x + 1]
		|| map->grid[y][x + 1] == ' '))
		return (1);
	if (y > 0 && (x > (int)ft_strlen(map->grid[y - 1])
			|| !map->grid[y - 1][x] || map->grid[y - 1][x] == ' '))
		return (1);
	if (y < map->height - 1 && (x > (int)ft_strlen(map->grid[y + 1])
			|| !map->grid[y + 1][x] || map->grid[y + 1][x] == ' '))
		return (1);
	return (0);
}

int	check_map(t_game *map)
{
	int		y;
	int		x;
	int		len;
	char	c;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		len = (int)ft_strlen(map->grid[y]);
		while (x < len)
		{
			c = map->grid[y][x];
			if (c == '0' || is_player_char(c))
			{
				if (is_adjacent_to_space(x, y, map))
					return (handle_error(map, \
						"Error\nLa carte doit être fermé\n"), 1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

void	pad_map_lines(t_game *map)
{
	int		max_width;
	int		y;
	int		len;

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
		replace_spaces_with_walls(map, y);
		len = ft_strlen(map->grid[y]);
		if (len < map->width)
			pad_lines(map, len, y);
		else
			map->grid[y][map->width] = '\0';
		y++;
	}
}

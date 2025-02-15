/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artheon <artheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:41:10 by artheon           #+#    #+#             */
/*   Updated: 2025/02/15 14:42:12 by artheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

char	*check_error(char *file_content, t_config **config)
{
	char	**lines;
	char	*map_location;
	int		i;
	int		count_element;

	lines = ft_split(file_content, '\n');
	map_location = NULL;
	i = 0;
	count_element = 0;
	while (lines[i])
	{
		if(is_valid_map_line(lines[i]))
		{
			map_location = ft_strdup(lines[i]);	
			if (!map_location)
				return (NULL);
			break ;
		}
		if(checking_map_element(lines[i], &count_element, config) == 1)
		{
			free_split(lines);
			return (NULL);
		}	
		i++;
	}
	free_split(lines);
	if (count_element != 6)
	{
		if (count_element < 6)
			error_exit("Error\nIl manque quelque chose dans la description\n", 0);	
		else
			error_exit("Error\nUn élément est en trop dans la description\n", 0);
		return (NULL);
	}
	if (!map_location)
		error_exit("Error\nCarte non trouvée dans le fichier.\n", 0);
	return (map_location);
}

bool	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

bool	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

t_game	*parse_map(char *map_section, t_config *config)
{
	char	**lines;
	char	*new_line;
	t_game	*map;
	size_t	nbrdechaines;
	int		i;
	int		y;
	int		x;
	int		len;
	int		start;
	int		player_count;
	int		temp;
	
	lines = NULL;
	map = malloc(sizeof(t_game));
	if (!map)
	{
		error_exit("Allocation mémoire échoué.\n", 0);
		return (NULL);
	}
	ft_memset(map, 0, sizeof(t_game));
	i = 0;
	nbrdechaines = 0;
	player_count = 0;
	while (map_section[i])
	{
		if (!is_valid_map_char(map_section[i]) && map_section[i] != '\n')
		{
			free(map);
			error_exit("Caractère invalide dans la carte.\n", 0);
			return (NULL);
		}
		if (is_player_char(map_section[i]))
			player_count++;
		if (map_section[i] == '\n' || map_section[i + 1] == '\0')
			nbrdechaines++;
		i++;
	}
	if (player_count != 1)
	{
		free(map);
		error_exit("Il doit y avoir exactement un joueur sur la carte.\n", 0);
		return (NULL);
	}
	lines = ft_calloc(nbrdechaines + 1, sizeof(char *));
	if (!lines)
	{
		free(map);
		error_exit("Allocation mémoire échoué\n", 0);
		return (NULL);
	}
	i = 0;
	nbrdechaines = 0;
	start = 0;
	while (map_section[i])
	{
		if (map_section[i] == '\n' || map_section[i + 1] == '\0')
		{
			if (map_section[i] == '\n')
				lines[nbrdechaines] = ft_substr(map_section, start, i - start + 0);
			else
				lines[nbrdechaines] = ft_substr(map_section, start, i - start + 1);
			if (!lines[nbrdechaines])
			{
				free_split(lines);
				free(map);
				error_exit("Allocation mémoire échoué\n", 0);
				return (NULL);
			}
			if (lines[nbrdechaines][0] == '\0')
			{
				free_split(lines);
				free(map);
				error_exit("Ligne vide dans la carte.\n", 0);
				return (NULL);
			}
			nbrdechaines++;
			start = i + 1;
		}
		i++;
	}
	map->grid = lines;
	map->height = (int)nbrdechaines;
	map->width = ft_strlen(lines[0]);
	map->config = config;
	i = 1;
	while (lines[i])
	{
		temp = ft_strlen(lines[i]);
		if (map->width < temp)
			map->width = temp;
		i++;
	}
	len = 0;
	y = 0;
	x = 0;
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
				return (NULL);	
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
	y = 0;
	x = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x] != '1' && (y == 0 || y == map->height - 1 || x == 0 || x == (int)ft_strlen(map->grid[y]) - 1))
			{
				free_split(map->grid);
				free(map);
				error_exit("La carte doit être fermée par des murs.", 0);
				return (NULL);
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
	return (map);
}